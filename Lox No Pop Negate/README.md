*"To interpret OP_NEGATE, we pop the operand, negate the value, and then push the result. That’s a simple implementation, but it increments and decrements stackTop unnecessarily, since the stack ends up the same height in the end. It might be faster to simply negate the value in place on the stack and leave stackTop alone."*

*- Nystrom, From Crafting Interpreters*

**vm.c:**
1. In InterpretResult(), change the OP_NEGATE case to simply make the top of the stack vaalue a negative version of it rather than popping and pushing.


*The binary operations (add, subtract, multiply, divide, etc.) can use the same pattern where we can just pop one number and then simply do the operation and replace the other number in the stack rather than popping 2 then pushing one.*






