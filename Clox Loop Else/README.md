*This is an else statement that runs when a loop never enters its body.*


**compiler.c:**
1. Make a hidden local in whileStatement() that tracks whether the loop ever ran or not. If it did, we jump over the else statement. If it didn't, we run what is in the else.