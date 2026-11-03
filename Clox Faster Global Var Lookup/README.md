*"Looking up a global variable by name in a hash table each time it is used is pretty slow, even with a good hash table." We can make this more efficient by resolving global names to array slots at compile time.*

*"When compiling a reference to a global variable, we see if we've ever encountered its name before. If so, we know what index the value will be in in the globalValues array. Otherwise, we add a new empty undefined value in the array and then store a new hash table entry binding the name to that index."*

**value.h:**
1. Add an UNDEFINED sentinel type for global variable slot not being defined yet.

**vm.h:**
1. Replace globals table with global name table and global value array. The value array is where the global variable values live. The hash table maps the name of a global variable to its index in the value array.

**vm.c:**
1. Adjust initVM() and freeVM() to init and free new table.
2. Adjust global cases in the switch case so that the operand for the instruction is directly fromt he index of the global variable in the globalValues array.

**compiler.c:**
1. Replace identifierConstant() for globals.


