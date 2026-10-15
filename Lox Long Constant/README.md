**chunk.h:**
1. Add new OP_CONSTANT_LONG enum and define writeConstant() function which adds value to chunk’s constant array and then writes an appropriate instruction to load the constant.


**chunk.c:**
1. Implement writeConstant(), which will write a normal constant or long constant depending on the if the constants fit in one byte. We use little-endian when writing.

**debug.c:**
1. Implement constantLongInstruction() and then add the case for OP_CONSTANT_LONG. This will properly disassemble the instruction for long constant.

