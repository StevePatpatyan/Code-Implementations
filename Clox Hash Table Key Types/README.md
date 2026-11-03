*"In clox, we happen to only need keys that are strings, so the hash table we built is hardcoded for that key type. If we exposed hash tables to Lox users as a first-class collection, it would be useful to support different kinds of keys.*

*Add support for keys of the other primitive types: numbers, Booleans, and nil. Later, clox will support user-defined classes."*

**table.h:**
1. Replace key's type from ObjString* to just Value to support any of the primitve types as key.

**value.h:**
1. Add empty ValueType to differentiate nil from a key that is nil.
2. Add functions for generating hash values.

**table.c:**
1. Adjust all of the functions for the change of key from ObjString* to Value type. NULL will be EMPTY_VAL for nil keys and we check for nil key with IS_EMPTY.