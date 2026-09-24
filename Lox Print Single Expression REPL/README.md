See run() method in Lox.java. We add the check to see if the line is a single expression and if it is a REPL expression. If so, we evaluate and print the result. Otherwise, go about interpreting as normal. Note that we still resolve before doing any type of evaluation, including a single REPL expression. In runPrompt(), we change run(line) to run(line, true) indicating that we are running from the REPL. For running file, we use run(source, false). This implementation requires adding a semicolon after expressions. We are detecting single expressions AFTER parsing rather than during.

I also add/reveal a new interpret() method in Interpreter.java just for expressions to avoid removing private from the evaluate and stringify methods there.

Try typing these into the REPL (run Lox class without a file arg):

1 + 2
x (declare x first)
"hello" + " world"
true
nil