expression     → ternary ;
ternary        → equality ( "?" expression ":" ternary )? ;
equality       → comparison ( ( "!=" | "==" ) comparison )* ;
comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
term           → factor ( ( "-" | "+" ) factor )* ;
factor         → unary ( ( "/" | "*" ) unary )* ;
unary          → ( "!" | "-" ) unary
               | primary ;
primary        → NUMBER | STRING | "true" | "false" | "nil"
               | "(" expression ")" ;

# This uses the initial grammar structure from *Crafting Interpreters* Chapter 6 with comma expressions added in. There is right associativity because the rightmost ocnditional has to be evaluated first before it can evaluate the leftmost ternaries. QUESTION and COLON token types added in TokenType.java and Scanner.java and Expr.Ternary added.