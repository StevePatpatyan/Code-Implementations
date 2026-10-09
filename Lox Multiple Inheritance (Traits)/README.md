**GenerateAst.java:**
1. Add Trait node and traits field on the Class node.

**TokenType.java:**
1. Add TRAIT and WITH keywords.

**Scanner.java:**
1. Add trait and with to keywords.

**Parser.java:**
1. In declaration, match TRAIT to run traitDeclaration() method.
2. Create withClause() and traitDeclation() methods to handle trait integration.
3. Parse traits (call withClause()) and pass traits to Stmt.Class constructor in classDeclaration().

**Resolver.java:**
1. Add TRAIT to the ClassType enum.
2. Add visitTraitStmt() visitor for resolving traits.
3. Resolve traits in visitClassStmt().
4. Add check so that "super" can't be used in a trait, as this can cause issues.

**LoxTrait.java (This is a new file):**
1. Add LoxTrait class and appropriate properties.

**Interpreter.java:**
1. Add composeTraits() method, which will gather all of the trait methods and add it to the class. It will not override an method with the same name already in the class. Also add names() helper function for method names of the class with traits.
2. Add visitor method for trait interpretation. It will compose all traits methods and of course assign to environment.
3. Modify method building part in visitClassStmt() to compose its traits with composeTraits().

**AstPrinter.java:**
1. Add a visitor for trait for printing AST.