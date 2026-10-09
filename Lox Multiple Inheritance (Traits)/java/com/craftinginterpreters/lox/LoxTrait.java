package com.craftinginterpreters.lox;

import java.util.Map;

public class LoxTrait {
  final String name;
  final Map<String, LoxFunction> methods;

  LoxTrait(String name, Map<String, LoxFunction> methods) {
    this.name = name;
    this.methods = methods;
  }

  @Override
  public String toString() { return name; }
}
