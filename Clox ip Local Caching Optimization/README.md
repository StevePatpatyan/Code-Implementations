*"Reading and writing the ip field is one of the most frequent operations inside the bytecode loop. Right now, we access it through a pointer to the current CallFrame. That requires a pointer indirection which may force the CPU to bypass the cache and hit main memory. That can be a real performance sink. Ideally, we’d keep the ip in a native CPU register. C doesn’t let us require that without dropping into inline assembly, but we can structure the code to encourage the compiler to make that optimization. If we store the ip directly in a C local variable and mark it register, there’s a good chance the C compiler will accede to our polite request. This does mean we need to be careful to load and store the local ip back into the correct CallFrame when starting and ending function calls"*

**vm.c:**
1. In run(), store frame's ip in a register byte and change the macros to read from the register instead of the CallFrame object, including the READ ones and DEBUG_TRACE_EXECUTION.
2. Have the cases for jumps also access the local ip register.
3. In the OP_CALL case, store the caller's ip into the frame before pushing the new frame, then store the new frame's ip into the register.
4. In case OP_RETURN, put the caller's (previous) frame's ip into the local register.
5. Before every runtimeError(), store the saved ip into the frame's ip before throwing.


**Benchmarks:**
1. call.lox stresses call and return where the extra save and load costs show.
2. loop.lox is where the ip is touched on almost every instruction. This will show inprovement vs. the unmodified code and generally be better than call.lox performance.
3. Test with clox_chapters/chap24_calls code in the repo to compare performance between unmodified and this modified code.