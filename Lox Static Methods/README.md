**GenerateAst.java:**
1. Add a new field to the class statement for static or "class" methods.

**Parser.java:**
1. In classDeclaration(), separate static methods from standard methods by adding new array list and adding check.

**Stmt.java:**
1. Add classMethods property to Class.

**Resolver.java:**
1. Resolve the class methods in visitClassStmt().

**LoxClass.java:**
1. Make LoxClass extend LoxInstance so that the class object can be an instance of instance, so it can support calling a method from just the class name rather than needing an object instance. Add metaclass parameter to constructor.

**LoxInstance.java:**
1. Since the metaclass klass value is null, add a check into the get() method for this case.

**Interpreter.java:**
1. Add metaclass support and classMethods mapper in visitClassStmt().