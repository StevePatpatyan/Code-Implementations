<h1>BETA LANGUAGE SEMANTICS:</h1>
<h2>

* When calling a method on a class, prefer the method highest on the class’s inheritance chain.

* Inside the body of a method, a call to inner looks for a method with the same name in the nearest subclass along the inheritance chain between the class containing the inner and the class of this. If there is no matching method, the inner call does nothing.

</h2>


**TokenType.java:**
1. Replace SUPER with INNER.

**Scanner.java:**
1. Replace putting "super" keyword with putting "inner" keyword.

**Expr.java:**
1. Replace Super Expr with Inner, including its related visitor method.

**GenerateAst.java:**
1. Replace "Super" node with "Inner".

**Parser.java:**
1. Replace SUPER parsing branch with INNER logic.

**LoxClass.java:**
1. Prioritize finding superclass's method first by putting the check before the standard methods.get(name) code in findMethod()

**LoxFunction.java:**
1. Add the field declaringClass to have the function remember the class it was declared from at that point.
2. Make findInner() method to find the inner class method of the declaring class and define the inner and declaring class instances in the environment in bind() of the current class instance. I make LoxClass "methods" and LoxInstance "klass" fields protected instead of private.


**Interpreter.java:**
1. Replace visitSuperExpr() with visitInnerExpr().
2. Remove super environment blocks in visitClassStmt() and adjust LoxFunction objects visitClassStmt() and visitFunctionStmt().

**Resolver.java:**
1. Remove "super" scope including subclass type and errors and add "inner" scope in visitClassStmt().
2. Replace visitSuperExpr() with visitInnerExpr().

**AstPrinter.java:**
1. Add visitInnerExpr() and remove visitSuperExpr().



