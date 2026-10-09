//> Functions lox-function
package com.craftinginterpreters.lox;

import java.util.ArrayDeque;
import java.util.Deque;
import java.util.List;

class LoxFunction implements LoxCallable {
  private final Stmt.Function declaration;
//> closure-field
  private final Environment closure;
  
//< closure-field
/* Functions lox-function < Functions closure-constructor
  LoxFunction(Stmt.Function declaration) {
*/
/* Functions closure-constructor < Classes is-initializer-field
  LoxFunction(Stmt.Function declaration, Environment closure) {
*/
//> Classes is-initializer-field
  private final boolean isInitializer;
  private final LoxClass declaringClass;

  LoxFunction(Stmt.Function declaration, Environment closure,
              boolean isInitializer, LoxClass declaringClass) {
    this.isInitializer = isInitializer;
//< Classes is-initializer-field
//> closure-constructor
    this.closure = closure;
//< closure-constructor
    this.declaration = declaration;
    this.declaringClass = declaringClass;
  }
//> Classes bind-instance
  LoxFunction bind(LoxInstance instance) {
    Environment environment = new Environment(closure);
    environment.define("this", instance);
    environment.define("inner", findInner(instance));
/* Classes bind-instance < Classes lox-function-bind-with-initializer
    return new LoxFunction(declaration, environment);
*/
//> lox-function-bind-with-initializer
    return new LoxFunction(declaration, environment,
                           isInitializer, declaringClass);
//< lox-function-bind-with-initializer
  }
  private LoxCallable findInner(LoxInstance instance) {
    Deque<LoxClass> path = new ArrayDeque<>();
    for (LoxClass c = instance.klass;
         c != null && c != declaringClass;
         c = c.superclass) {
    // last pushed is the closest to declaringClass
      path.push(c);
    }

    while (!path.isEmpty()) {
      LoxFunction method = path.pop().methods.get(declaration.name.lexeme);
      if (method != null) return method.bind(instance);
    }

    // inner() does nothing here
    final int arity = declaration.params.size();
    return new LoxCallable() {
      @Override public int arity() { return arity; }
      @Override public Object call(Interpreter interpreter, List<Object> args) {
        return null;
      }
      @Override public String toString() { return "<native inner>"; }
    };
  }
//< Classes bind-instance
//> function-to-string
  @Override
  public String toString() {
    return "<fn " + declaration.name.lexeme + ">";
  }
//< function-to-string
//> function-arity
  @Override
  public int arity() {
    return declaration.params.size();
  }
//< function-arity
//> function-call
  @Override
  public Object call(Interpreter interpreter,
                     List<Object> arguments) {
/* Functions function-call < Functions call-closure
    Environment environment = new Environment(interpreter.globals);
*/
//> call-closure
    Environment environment = new Environment(closure);
//< call-closure
    for (int i = 0; i < declaration.params.size(); i++) {
      environment.define(declaration.params.get(i).lexeme,
          arguments.get(i));
    }

/* Functions function-call < Functions catch-return
    interpreter.executeBlock(declaration.body, environment);
*/
//> catch-return
    try {
      interpreter.executeBlock(declaration.body, environment);
    } catch (Return returnValue) {
//> Classes early-return-this
      if (isInitializer) return closure.getAt(0, "this");

//< Classes early-return-this
      return returnValue.value;
    }
//< catch-return
//> Classes return-this

    if (isInitializer) return closure.getAt(0, "this");
//< Classes return-this
    return null;
  }
//< function-call
}
