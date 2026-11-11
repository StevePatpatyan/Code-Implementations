**object.h:**
1. Add arity to the Native object struct and newNative().

**object.c:**
1. Add arity assignment into the newNative() declaration implementation.

**vm.c:**
1. Update defineNative() so it takes in arity now.
2. Check arity matches argCount in callValue(). We have to change the NativeFn to be a whole ObjNative* and adjust accordingly in the function and changing the AS_NATIVE macro.
3. In initVM(), update the clock native definition by adding arity argument.