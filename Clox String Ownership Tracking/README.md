*"When we create the ObjString for each string literal, we copy the characters onto the heap. That way, when the string is later freed, we know it is safe to free the characters too.*

*This is a simpler approach but wastes some memory, which might be a problem on very constrained devices. Instead, we could keep track of which ObjStrings own their character array and which are “constant strings” that just point back to the original source string or some other non-freeable location. Add support for this."*


**object.h:**
1. Add a bool in ObjString to track ownership.
2. Add referenceString() function to create non-owning strings.

**object.c:**
1. Add referenceString() function to create non-owning strings. Adjust allocateString() function and calls to include the ownsChars bool.
2. Change the printf statement in printObject() to no longer assume the strings are null-terminated.

**memory.c:**
1. Adjust the OBJ_STRING case in freeObject() to check if string object owns the chars before freeing it.


