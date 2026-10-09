package com.craftinginterpreters.lox;

import java.util.ArrayList;
import java.util.List;

class LoxList {
  final List<Object> elements;

  LoxList(List<Object> elements) {
    this.elements = new ArrayList<>(elements);
  }

  @Override
  public String toString() {
    StringBuilder sb = new StringBuilder("[");
    for (int i = 0; i < elements.size(); i++) {
      if (i > 0) sb.append(", ");
      Object e = elements.get(i);
      // Strings print quoted inside a list so ["a", 1] is unambiguous.
      sb.append(e instanceof String ? "\"" + e + "\"" : stringifyElement(e));
    }
    return sb.append("]").toString();
  }

  private static String stringifyElement(Object o) {
    if (o == null) return "nil";
    if (o instanceof Double) {
      String text = o.toString();
      if (text.endsWith(".0")) text = text.substring(0, text.length() - 2);
      return text;
    }
    return o.toString();
  }
}
