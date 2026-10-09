**Parser.java:**
1. Allow parameters to be null by initializing a parameters list to null and adding a check to allow for no parentheses with parameters for a method (that will be a getter method.) in function() method.

**Resolver.java:**
1. Check for null parameters value in resolveFunction() so it doesn't make an error when going through function.params.

**LoxFunction.java:**
1. Modify arity() and call() methods to handle null params.
2. Add isGetter() helper method.

**Interpreter.java:**
1. In visitGetExpr(), invoke getter method immediately.