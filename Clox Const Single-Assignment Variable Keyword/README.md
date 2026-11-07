*"Many languages make a distinction between variables that can be reassigned and those that can’t. In Java, the final modifier prevents you from assigning to a variable. In JavaScript, a variable declared with let can be assigned, but one declared using const can’t. Swift treats let as single-assignment and uses var for assignable variables. Scala and Kotlin use val and var."*


**scanner.h:**
1. Add token for const in the enum.

**scanner.c:**
1. Recognize const keyword in case 'c' in identifierType().

**compiler.c:**
1. Add a bool in Local struct to track if local is a const.
2. Since the compiler cannot see globals, add a table for marking globals as constant and also functions for marking and checking if the global is a constant.
3. Add isConst implementation through addLocal() and declareVariable().
4. In parseVariable() use our markGlobal() to mark globals as const in our new table and edit declareVariable() call inside there to add the isConst attribute. Adjust the parseVariable() call in varDeclaration() to include the isConst argument.
5. In declaration(), put a check if its a TOKEN_CONST or TOKEN_VAR. Call varDeclaration with the appropriate isConst value, respectively. Add TOKEN_CONST in synchronize() to include it.
6. In namedVariable(), reject assignment attempts to a const.

I made it to still allow nil/undefined constants. Otherwise, we can set a check in varDeclaration().


Test with test.lox. make clox first, then run ./clox test.lox