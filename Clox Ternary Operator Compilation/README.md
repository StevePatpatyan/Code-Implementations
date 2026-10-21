**scanner.h:**
1. Add question mark and colon tokens.

**scanner.c:**
1. Add the matching case for the new tokens in scanToken().

**compiler.c:**
1. Add PREC_CONDITIONAL precedence into the precedence enum. It has the lowest precedence except to assignment.
2. Add the parse rules for TOKEN_QUESTION and TOKEN_COLON in rules[].
3. Make conditional() function to properly parse the conditional operation. Start with parse precedence of PREC_CONDITIONAL during then branch, then PREC_ASSIGNMENT for else branch.