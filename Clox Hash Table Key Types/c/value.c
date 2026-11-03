#include <stdio.h>
#include <string.h>

#include "object.h"
#include "memory.h"
#include "value.h"

void initValueArray(ValueArray* array) {
  array->values = NULL;
  array->capacity = 0;
  array->count = 0;
}

void writeValueArray(ValueArray* array, Value value) {
  if (array->capacity < array->count + 1) {
    int oldCapacity = array->capacity;
    array->capacity = GROW_CAPACITY(oldCapacity);
    array->values = GROW_ARRAY(Value, array->values,
                               oldCapacity, array->capacity);
  }

  array->values[array->count] = value;
  array->count++;
}

void freeValueArray(ValueArray* array) {
  FREE_ARRAY(Value, array->values, array->capacity);
  initValueArray(array);
}

void printValue(Value value) {
  switch (value.type) {
    case VAL_BOOL:
      printf(AS_BOOL(value) ? "true" : "false");
      break;
    case VAL_NIL: printf("nil"); break;
    case VAL_NUMBER: printf("%g", AS_NUMBER(value)); break;
    case VAL_OBJ: printObject(value); break;
  }
}

bool valuesEqual(Value a, Value b) {
  if (a.type != b.type) return false;
  switch (a.type) {
    case VAL_BOOL:   return AS_BOOL(a) == AS_BOOL(b);
    case VAL_NIL:    return true;
    case VAL_NUMBER: return AS_NUMBER(a) == AS_NUMBER(b);
    case VAL_OBJ:    return AS_OBJ(a) == AS_OBJ(b);
    default:         return false; // Unreachable.
  }
}

// adapted from Thomas Wang's 64-bit mixing hash
static uint32_t hashBits(uint64_t bits) {
  bits = ~bits + (bits << 18);
  bits ^= bits >> 31;
  bits *= 21;
  bits ^= bits >> 11;
  bits += bits << 6;
  bits ^= bits >> 22;
  return (uint32_t)(bits & 0x3fffffff);
}

uint32_t hashValue(Value value) {
  switch (value.type) {
    case VAL_BOOL:   return AS_BOOL(value) ? 3 : 5;
    case VAL_NIL:    return 7;
    case VAL_NUMBER: {
      double d = AS_NUMBER(value);
      if (d == 0) d = 0;
      uint64_t bits;
      memcpy(&bits, &d, sizeof(bits));
      return hashBits(bits);
    }
    case VAL_OBJ:
      if (IS_STRING(value)) return AS_STRING(value)->hash;
      return 0;
    default: return 0;
  }
}