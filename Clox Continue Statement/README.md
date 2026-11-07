**scanner.h:**
1. Add continue token type.

**scanner.c:**
1. Add case to scan TOKEN_CONTINUE in identifierType().

**compiler.c:**
1. Add two globals for compiler which tracks both the innermost loop starting point, so where to jump to, and the loop's scope depth so we know how to clean up locals.
2. Add continueStatement() which the keyword dispatches to. This will check if the program is in a loop, and if so, it will discard the locals up to the depth and will jump up to the condition.
3. Check for continue token in statement().
4. In whileStatement() and forStatement(), save and restore the loop state around the body, so nested loops and sibling loops work.