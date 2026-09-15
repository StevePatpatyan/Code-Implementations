expression     → equality ;
comma          -> equality ( "," equality )*
equality       → comparison ( ( "!=" | "==" ) comparison )* ;
comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
term           → factor ( ( "-" | "+" ) factor )* ;
factor         → unary ( ( "/" | "*" ) unary )* ;
unary          → ( "!" | "-" ) unary
               | primary ;
primary        → NUMBER | STRING | "true" | "false" | "nil"
               | "(" expression ")" ;

# This uses the initial grammar structure from *Crafting Interpreters* Chapter 6 with comma expressions added in. It is low precedence, so before assignment/equality but after expression. There is left-to-right associativity. Also, the function call is considered, so the finishCall() function is changed so that the arguments have a higher precedence than commas so that they aren't parsed as one argument. ( See the arguments.add(equality()) line )