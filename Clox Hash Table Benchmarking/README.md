**GO TO "c" FOLDER AND RUN "make benchmarks" TO COMPILE AND "./benchmarks" TO RUN HASH TABLE BENCHMARK PROGRAM.**

<h1>CASES</h1>

**Case 1: Insert from empty**

    Steps:
        1. Builds 1,000,000 string keys (“key0”, “key1”, ... “key999999”), each with its FNV-1a hash precomputed. This happens before the timer starts so key creation isn’t measured.
        2. Creates an empty table with initTable. Capacity is 0 and nothing is allocated yet.
        3. Starts the clock.
        4. Calls tableSet 1,000,000 times, once per key, with the loop index as the value.
        5. Stops the clock and prints the total time and nanoseconds per insert.
        6. Frees the table and keys.

    Explanation:
        This includes every rehash, so it measures the growth policy that is the 0.75 load factor and doubling and not just a single tableSet(). It should be several times slower per operation for every lookup because of allocation and re-insertion.


**Case 2: Lookup hits**

    Steps:
        1. Builds 1,000,000 keys (“key0” ... “key999999”) with hashes precomputed.
        2. Fills a table with all of them using tableSet. This is setup and is not timed.
        3. Shuffles the key array. This is so the keys are looked up in random order
        4. Starts the clock.
        5. Loops 5 times over all 1M keys, calling tableGet for each one. That would be 5 million lookups and every one succeeding. 
        6. Adds each returned value into accumulator so it actually lookups and calculatesl ookup time, and acc gets saved into sink at the end so the compiler can’t optimize the lookups for the next case.
        7. Stops the clock and prints nanoseconds per lookup.


**Case 3: Lookup misses** 

    Steps
        1. Builds two sets of 1,000,000 keys: keys (“key0” ... “key999999”) and miss (“nope0” ... “nope999999”). The names are different so none of the miss keys can match anything in the table.
        2. Fills the table with only the keys set. The miss keys are never inserted. This is not timed.
        3. Starts the clock.
        4. Loops 5 times over the miss keys, calling tableGet() on each. All of 5 million lookups should fail. It adds each result (true or false) into found, which should end up 0. 5. Like acc, found is saved into sink so the compiler can’t remove the loop process of doing the work.
        6. Stops the clock and prints nanoseconds per lookup.

    Explanation:
        A miss has to probe until it finds an empty slot so it’s the most sensitive test of clustering. At a 0.75 load factor with linear probing, misses should be much slower than hits. This showcases a good point for keeping the load factor from being too high because 
        there will be longer linear probing chains which take longer to lookup.


**Case 4: Delete/insert churn**
    Steps:
        1. Builds a pool of 400,000 keys (“churn0” ... “churn399999”) which is n * 4 so it is enough to cycle through.
        2. Pre-fills the table with the first 50,000 keys which is n / 2. This is untimed setup. Two counters track a sliding window of live keys, where head is the oldest one and tail is the next one to insert.
        3. Starts the clock.
        4. Runs 5,000,000 iterations. Each one deletes the oldest live key (the head) and inserts a fresh one (the tail), then advances both counters. The window of 50,000 live keys slides through the pool and wraps around when it reaches the end. A key is deleted and not re-inserted until about 350,000 operations later and so the live set never collides with itself.
        5. Stops the clock and prints nanoseconds per delete-plus-insert pair.
        6. Times 100,000 miss lookups on keys just ahead of tail, which are guaranteed not to be in the table. This is the measurement after churning.
        7. Prints count and capacity so you can see what state the table ended up in.


    Explanation:
        Churning means to continuously insert and delete from the table, like you see in the steps. The live count stays around 50k but tombstones accumulate. The book counts tombstones toward count, so the table resizes to clear them out. The benchmark prints count and capacity, and it times misses afterward. If miss lookups degrade after churning, tombstones are lengthening the probe chains.


<h2>I bypass FNV and set the hashes directly in three cases (ran by benchBadHash()):</h2>

**Case 5: hash = i:**
    This is the ideal edge case because there are no collisions.

**Case 6: hash = i*1024**
    This one will collide under the power-of-two mask hash & (capacity-1) until the capacity exceeds 1024. It shows how a power-of-two table behaves with strided hashes.

**Case 7: All hashes equal**
    This is the worst edge case because every operation is a linear scan, so it’s O(n^2). I kept n at 20k so it finishes quickly. The gap between this and the ideal case shows how much the table’s performance depends on the hash function.


**Case 8: Size sweep (100 to 4M keys)**
    Steps:
        For each size in 100, 1,000, 10,000, 100,000, 1,000,000, and 4,000,000:
            1. Builds that many keys and fills a fresh table with them.
            2. Shuffles the key array, so lookups hit the table in random order.
            3. Starts the clock.
            4. Does 20,000,000 lookups, cycling through the keys with keys[i % n]. For small n it loops over the same keys many times and for large n it covers them only a few times. Every lookup is a hit.
            5. Stops the clock and prints ns/lookup for that size.
            6. Frees everything before moving to the next size.
    Explanation:
        This is about hitting the different cache levels and comparing times. The table’s logic doesn’t change across sizes, but ns/op should step up as the working set spills out of L1, then L2, then L3, and finally into RAM.