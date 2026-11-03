#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
 
#include "common.h"
#include "object.h"
#include "table.h"
#include "value.h"
#include "vm.h"

VM vm;
 
static volatile double sink; // rule out dead-code elimination
 
static double now(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec + ts.tv_nsec * 1e-9;
}
 
// same FNV-1a the book uses
static uint32_t fnv(const char* key, int length) {
  uint32_t hash = 2166136261u;
  for (int i = 0; i < length; i++) {
    hash ^= (uint8_t)key[i];
    hash *= 16777619;
  }
  return hash;
}
 
// build a string object directly so we measure only the table
static ObjString* makeKey(const char* chars, int length, uint32_t hash) {
    ObjString* s = calloc(1, sizeof(ObjString));
    s->length = length;
    s->chars = malloc(length + 1);
    memcpy(s->chars, chars, length);
    s->chars[length] = '\0';
    s->hash = hash;
    return s;
}
 
static ObjString** makeKeys(int n, const char* fmt) {
    ObjString** keys = malloc(sizeof(ObjString*) * n);
    char buf[64];
    for (int i = 0; i < n; i++) {
        int len = snprintf(buf, sizeof buf, fmt, i);
        keys[i] = makeKey(buf, len, fnv(buf, len));
    }
    return keys;
}

// free all the keys after done with case
static void freeKeys(ObjString** keys, int n) {
    for (int i = 0; i < n; i++) { 
        free(keys[i]->chars);
        free(keys[i]);
    }
    free(keys);
}

// shuffle around keys
static void shuffle(ObjString** a, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = (int)(((uint64_t)rand() * 32768u + (uint64_t)rand()) % (uint64_t)(i + 1));
        ObjString* t = a[i];
        a[i] = a[j];
        a[j] = t;
    }
}

static void report(const char* name, long ops, double secs) {
    printf("  %-44s %9.1f ns/op  (%.3fs)\n", name, secs / ops * 1e9, secs);
}
 
// case 1: insert from empty 
// measures insert cost including all the rehashes
static void benchInsert(int n) {
    ObjString** keys = makeKeys(n, "key%d");

    Table t;
    initTable(&t);

    double s = now();
    for (int i = 0; i < n; i++) 
        tableSet(&t, keys[i], NUMBER_VAL(i));

    report("insert from empty", n, now() - s);

    freeTable(&t);
    freeKeys(keys, n);
}
 
// case 2: lookup hits
static void benchLookupHit(int n) {
    ObjString** keys = makeKeys(n, "key%d");

    Table t;
    initTable(&t);
  
    for (int i = 0; i < n; i++) 
        tableSet(&t, keys[i], NUMBER_VAL(i));
  
    shuffle(keys, n);

    Value v;
    double acc = 0;

    double s = now();
    for (int rep = 0; rep < 5; rep++) {
        for (int i = 0; i < n; i++) { 
            tableGet(&t, keys[i], &v);
            acc += AS_NUMBER(v);
        }
    }

    sink = acc;

    report("lookup hit (random order)", 5L * n, now() - s);
    freeTable(&t);
    freeKeys(keys, n);
}
 
// case 3: Lookup misses
static void benchLookupMiss(int n) {
    ObjString** keys = makeKeys(n, "key%d");
    ObjString** miss = makeKeys(n, "nope%d");

    Table t;
    initTable(&t);

    for (int i = 0; i < n; i++) 
        tableSet(&t, keys[i], NUMBER_VAL(i));

    Value v;
    int found = 0;
    double s = now();

    for (int rep = 0; rep < 5; rep++) {
        for (int i = 0; i < n; i++) 
            found += tableGet(&t, miss[i], &v);
    }

    sink = found;

    report("lookup miss", 5L * n, now() - s);

    freeTable(&t);
    freeKeys(keys, n);
    freeKeys(miss, n);
}
 
// case 4: Steady-state churn
static void benchChurn(int n, int ops) {
    int pool = n * 4;
    ObjString** keys = makeKeys(pool, "churn%d");

    Table t;
    initTable(&t);

    int live = n / 2;

    for (int i = 0; i < live; i++) 
        tableSet(&t, keys[i], NUMBER_VAL(i));

    int head = 0, tail = live; // FIFO of live keys
    double s = now();

    for (int i = 0; i < ops; i++) {
        tableDelete(&t, keys[head % pool]);
        head++;
        tableSet(&t, keys[tail % pool], NUMBER_VAL(i));
        tail++;
    }

    report("churn (delete one + insert one)", ops, now() - s);

    // lookup cost afterwards will show the damage tombstones did
    Value v;
    int found = 0;

    s = now();

    for (int i = 0; i < n; i++) 
        found += tableGet(&t, keys[(tail + i) % pool], &v);

    sink = found;

    report("  miss lookups after churn", n, now() - s);
    printf("  (count=%d capacity=%d)\n", t.count, t.capacity);

    freeTable(&t);
    freeKeys(keys, pool);
}
 
// case 5,6,7: Bad hashes
// mode 0: all keys hash to 17
// mode 1: hash = i * 1024
// mode 2: hash = i
static void benchBadHash(int n, int mode) {
    ObjString** keys = malloc(sizeof(ObjString*) * n);
    char buf[32];

    for (int i = 0; i < n; i++) {
        int len = snprintf(buf, sizeof buf, "k%d", i);
        uint32_t h = mode == 0 ? 17u : mode == 1 ? (uint32_t)i * 1024u : (uint32_t)i;
        keys[i] = makeKey(buf, len, h);
    }

  Table t;
  initTable(&t);

  double s = now();

    for (int i = 0; i < n; i++) 
        tableSet(&t, keys[i], NUMBER_VAL(i));

    Value v;
    double acc = 0;

    for (int i = 0; i < n; i++) { 
        tableGet(&t, keys[i], &v); acc += AS_NUMBER(v);
    }

    sink = acc;

    const char* names[] = {"all hashes equal (O(n^2))", "hash = i*1024 (stride)",
                         "hash = i (sequential)"};

  report(names[mode], 2L * n, now() - s);

  freeTable(&t);
  freeKeys(keys, n);
}
 
// case 8: Size sweep
static void benchSizeSweep(void) {
  int sizes[] = {100, 1000, 10000, 100000, 1000000, 4000000};
    for (int k = 0; k < 6; k++) {
        int n = sizes[k];
        ObjString** keys = makeKeys(n, "s%d");

        Table t;
        initTable(&t);

        for (int i = 0; i < n; i++) 
            tableSet(&t, keys[i], NUMBER_VAL(i));
        
        shuffle(keys, n);
    
        long ops = 20000000L;
    
        Value v;
        double acc = 0;

        double s = now();
        
        for (long i = 0; i < ops; i++) {
            tableGet(&t, keys[i % n], &v);
            acc += AS_NUMBER(v);
        }

        sink = acc;
        char name[64];
        
        snprintf(name, sizeof name, "random lookup, n = %d", n);
        report(name, ops, now() - s);
        
        freeTable(&t);
        freeKeys(keys, n);
  }
}
 
int main(void) {
    srand(12345);
    printf("== insert ==\n");
    benchInsert(1000000);
    printf("== lookups (n = 1,000,000) ==\n");
    benchLookupHit(1000000);
    benchLookupMiss(1000000);
    printf("== churn / tombstones (n = 100,000) ==\n");
    benchChurn(100000, 5000000);
    printf("== pathological hashes (n = 20,000) ==\n");
    benchBadHash(20000, 2);
    benchBadHash(20000, 1);
    benchBadHash(20000, 0);
    printf("== size sweep ==\n");
    benchSizeSweep();
    return 0;
}