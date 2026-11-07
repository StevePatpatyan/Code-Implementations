**chunk.h:**
1. Add OP_GET_LOCAL_LONG and OP_SET_LOCAL_LONG. Keep the other OPs as an option so it doesn't use an extra byte for the operand when it has fewer than 256 in a scope. Because it doesn't need it.

**common.h:** Add definition for UINT_16_COUNT.

**compiler.c:**
1. Make the locals array in the Compiler growable, adding a UINT16 option. Also update initCompiler() and FREEARRAY in endCompiler().
2. In addLocal(), raise limit to 2 bytes and make array grow dynamically.
3. In namedVariable(), make the right operation emit depending on number of slots.

**vm.h:**
1. Add macro for reading 16-bit.
2. update STACK_MAX to handle more.

**vm.c:**
1. Add cases for OP_GET_LOCAL_LONG and OP_SET_LOCAL_LONG.

**debug.c:**
1. Add dissassembly instructions for our new operations.