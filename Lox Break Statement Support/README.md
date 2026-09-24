**Scanner.java:**
1. Add break keyword (```keywords.put("break", BREAK)```)

**TokenType.java:**
1. Add BREAK token type enum (keywords area)

**GenerateAST.java:**
1. Add a new statement type to the list of Stmt subclasses (I put it under "While" type)

**Stmt.java:**
1. Add Break subclass extending Stmt
2. Add visitBreakStmt visitor method in visitor interface

**Interpreter.java:**
1. Define visitBreakStmt visitBreakStmt method. It should throw a BreakException on visit to handle the break behavior.
2. Make BreakException as RuntimeException

**Parser.java:**
1. Add BREAK to statement method/parser
2. Define breakStatement method which is what is called after break is matched by parser
3. Track if inside a loop with loopDepth int var. Throw error in breakStatement method if outside of a loop (loopDepth == 0)
4. Add 1 to loop depth before body statement and subtract after in whileStatement() and forStatement(). This represents one while loop being +1 loop depth in. After running the body, the loop exits, so -1 loop depth.
5. Catch break in a while loop by adding try catch for a BreakException in visitWhileStmt()
6. In function method, since it needs to have its own loopDepth and not carry on with the enclosing loop depth, we need to store the original loop depth, reset loopDepth to 0, and carry on with the function before reassigning the enclosing loop depth back to loopDepth.

**Resolver.java:**
1. Implement visitBreakStmt method in resolver (simple).


**AstPrinter.java:**
1. Implement visitBreakStmt method in AST printer (just needs a simple implementation).


*See test Lox files in java folder to test cases.*