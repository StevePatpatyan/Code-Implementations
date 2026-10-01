**Environment.java:**
1. Add a new List<Object> for local variables which are the slots for the index-based, and keep the original "values" map for globals. Adjust getAt() and assignAt() methods for locals and index instead of name accordingly, including adding defineLocal() method.

**Resolver.java:**
1. Replace private final Stack<Map<String, Boolean>> scopes = new Stack<>(); with private final Stack<Map<String, Variable>> scopes = new Stack<>(); and add a Variable inner class that stores if variable is defined and now its index.
2. Change declare(), define(), and beginScope() to reflect "scopes" variable structure changes. Use scope.size() in declare() as next index.
3. Change visitVariableExpr() to handle the conditional for reading variable in its own initializer according to new scopes list structure change.
4. In visitClassStmt(), set the index of "super" and "this".
4. Change resolveLocal() to resolve with index on top of depth. We change the interpreter's resolve method now to consider index.

**Interpreter.java:**
1. Replace private final Map<Expr, Integer> locals = new HashMap<>(); with private final Map<Expr, Location> locals = new HashMap<>(); and build the respective class for Location which stores both depth and index.
2. Change resolve() to put into locals with the index as well now.
3. Change lookUpVariable() and visitAssignExpr() to use index.
4. Add defineVariable() helper function so that the environment can define variables properly, depending on if they are global or local.
5. In visitClassStmt(), visitVarStmt(), and visitFunctionStmt() run the new defineVariable() instead of the old environment.define() and environment.assign() methods.
6. Change visitSuperExpr() to adjust for structure changes. "this" has index of 0 and its depth is the superclass's depth - 1.

**LoxFunction.java:**
1. Edit the bind() and call() functions to use the environments defineLocal() instead of define() and change getAt() arguments accordingly. Again, "this" index is always 0.