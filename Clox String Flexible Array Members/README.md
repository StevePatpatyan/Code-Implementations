*"Each string requires two separate dynamic allocations—one for the ObjString and a second for the character array. Accessing the characters from a value requires two pointer indirections, which can be bad for performance. A more efficient solution relies on a technique called flexible array members. Use that to store the ObjString and its character array in a single contiguous allocation."*

**object.h:**
1. Change char* chars to char chars[] in the ObjString struct so that chars lives directly inside the struct rather than being in a separate heap block.
2. Remove takeString() which just allocating the old chars pointer object.
3. Add allocateString() so that it can be used by vm.c

**object.c:**
1. In allocateString() use allocateObject() to allocate struct size and now + however many characters are in the string to the struct now that chars is a part of it directly (previously used ALLOCATE_OBJ but now we have to customize).
2. Remove takeString().
3. Adjust copyString() as well to use the new chars[] and copy straight from ObjString.
4. Remove static keyword of allocateString().

**vm.c:**
1. Change concatenate() to build straight into the ObjString.

**memory.c:**
1. In freeObject, for case OBJ_STRING, adjust to our new flexible array member style so it just reallocates the object to free it.