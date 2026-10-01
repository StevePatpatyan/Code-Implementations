**Resolver.java:**
1. Add an inner class to store both whether a variable is defined AND whether or not it has been used. Store token name in here to reference it for the error.
2. Change the scope stack (called private final Stack<Map<String, Boolean>> scopes = new Stack<>()) to use VariableInfo instead of just Boolean as the map value.
3. In declare(), replace Map<String, Boolean> scope = scopes.peek(); with Map<String, VariableInfo> scope = scopes.peek();, and replace scope.put(name.lexeme, false); with scope.put(name.lexeme, new VariableInfo(name));
4. In define(), replace scopes.peek().put(name.lexeme, true); with scopes.peek().get(name.lexeme).defined = true;
5. In visitVariableExpr() change the initializer check to mark variables as used/unused.
6. We also need to change the scope peeking methods code for "super" and "this" in visitClassStmt. We use the checkUnused property of VariableInfo class to avoid checking "super" and "this" as unused variable since thay are special cases.
6. In beginScope() replace scopes.push(new HashMap<String, Boolean>()); with scopes.push(new HashMap<String, VariableInfo>());
7. In endScope(), on top of popping the scope, check each variable and throw an error for unused variables in the scope. Throw an error if there is one found.