**scanner.h:**
1. Add token types for switch, case, default, and colon.

**scanner.c:**
1. Add colon token match in scanToken().
2. Add switch, case, and default identifier matching in identifierType() in their respective letter cases.

**compiler.c:**
1. Add ParseRule for colon in rules[].

**chunk.h:**
1. Make a duplicate operation to keep the switch statement's value around to compare each case to it.

**debug.c:**
1. Add dissasemble instruction for OP_DUP.

**vm.c:**
1. In run(), add the OP_DUP case which will push the operand into the stack.

**compiler.c:**
1. Add dispatching to a new function switchStatement() (check comments) if switch statement is found in statement(). Add a helper function endOfCaseBody() to run inside case body via statement() before moving on.