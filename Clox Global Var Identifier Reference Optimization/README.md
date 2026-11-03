*The compiler adds a global variable’s name to the constant table as a string every time an identifier is encountered. It creates a new constant each time, even if that variable name is already in a previous slot in the constant table. That’s wasteful in cases where the same variable is referenced multiple times by the same function. That, in turn, increases the odds of filling up the constant table and running out of slots since we allow only 256 constants in a single chunk.*

**compiler.c:**
1. Add a table of string constants so we can just reference it for globals and not make a new constant each time the identifier is encountered.
2. Change identifierConstant() to get the index value of the constant from the identifier from the table we made if it's in there. Otherwise, we make the constant and set it in the table to reuse and return the index as usual.
3. Add initTable() and freeTable() at the start and end of compile(), respectively, for the table.



We have a slightly worse time factor, although still constant, due to our constants hash table lookups, but we get more space for constants. No memory is saved from redundant strings because we intern strings anyway. Overall, this is a nice tradeoff.