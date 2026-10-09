
*For simplicity, we will have Lox refer to the dynamic array as a "list" like Python does.*

**TokenType.java:**
1. Add LEFT_BRACKET and RIGHT_BRACKET token types.

**Scanner.java:**
1. Add LEFT_BRACKET and RIGHT_BRACKET in scanToken().

**GenerateAst.java:**
1. Add ListLiteral, and Index and IndexSet (Getter and Setter) nodes to the Expr list.

**Parser.java:**
1. Add suppport for list literals in primary().
2. Treating indexing (finding a value in list by index) as a postfix operation, add support in the loop in call() (We have to match a LEFT_BRACKET).
3. Add index assignment in assignment().

**LoxList.java (This is a new file):**
1. Add LoxList class implementation. This is built off of Java's ArrayList. It has a toString() and stringifyElement() method, too.

**Resolver.java:**
1. Make visit methods for ListLiteral, Index, and IndexSet nodes for resolving the things inside of them.

**Interpreter.java:**
1. Add visitor methods for the interpreter to evaluate each literal, getting and setting index, as well as methods for checking that an object is a list and for checking the index.
2. Add Lox native functions for len(list or string), push(list, e), and pop(list). Add nativeError type error for these functions appropriately.

**AstPrinter.java:**
1. Add support for the new visitor methods.