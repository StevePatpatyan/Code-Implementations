**vm.h:**
1. Remove STACK_MAX, change stackTop to stackCount int and add stackCapacity as well.


**vm.c:**
1. Initilize new stackCapacity and stack properties in initVM().
2. Reset stackCount to 0 in resetStack().
3. Adjust pop() and push() to use stackCount properties instead of stackTop. For push(), we have to check if the stack is large enough and increase capacity if need to.
4. Modify the print loop in DEBUG_TRACE_EXECUTION where it prints each slot in the stack.
5. Include memory.h.


