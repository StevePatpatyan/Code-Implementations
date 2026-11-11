*"Right now, there’s no way for a native function to signal a runtime error. In a real implementation, this is something we’d need to support because native functions live in the statically typed world of C but are called from dynamically typed Lox land. If a user, say, tries to pass a string to sqrt(), that native function needs to report a runtime error."*


**object.h:**
1. Change NativeFn typedef to return as a bool instead of a Value. We will be using this to check if it succeeded and we are now storing in args[-1] of function instead of returning and pushing so no need for storing result in Value object anymore.

**vm.c:**
1. In the OBJ_NATIVE case in callValue(), check that the result returned successfully by checking its boolean indicating success is true. If it is, push the result into args[-1] where the callee was held. If it is false, call a runtimeError() instead, referring to args[-1] to see the message.
2. Keep in mind we are now pusing the result in the callee slot instead of popping args and callee then pushing. Update the existing clockNative() by moving result into args[-1] and returning a bool instead of returning. I also will make sqrt() native to show how the errors will work. For errors, make nativeError() helper function.
3. Define the sqrt() native in initVM() using defineNative().



**I added many native functions with test files named test_natives.lox and test_input.lox**
* floor - math flooring
* mod - modulo
* len - get length of a string
* substr - get substring of a string
* str - convert to string
* num - convert to number
* input - wait for user input

I also added macros to check arity, string and number.