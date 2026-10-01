**Expr.java:**
1. Add Function expression type by adding a Function expression subclass.
2. Consequently add the visitor method for the new expr into the Visitor interface.

**GenerateAst.java:**
1. Add Function to expression definitions.

**Parser.java:**
1. In our grammar, a function expression can now be considered a primary, so we can add "fun" structure to primary().
2. We also have to add a check in declaration(). If it has an IDENTIFIER, we return it as the normal declaration. Otherwise, we move it through so that it can be checked in primary().
2. Implement functionExpression() method so that the parser can properly handle the whole expression when it detects FUN token type match.

**Interpreter.java:**
1. Create visitor method for function expression.

**LoxFunction.java:**
1. Since declaration.name can be null now, edit the toString() method to account for this.

**AstPrinter.java:**
1. Implement visitor method for Function expression for the printer.

**Resolver.java:**
1. Implement visitor method.