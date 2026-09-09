package com.craftinginterpreters.lox;

import java.util.Arrays;

class RpnPrinter implements Expr.Visitor<String> {

    String print(Expr expr) {
        return expr.accept(this);
    }

    @Override
    public String visitBinaryExpr(Expr.Binary expr) {
        return expr.left.accept(this) + " "
             + expr.right.accept(this) + " "
             + expr.operator.lexeme;
    }

    @Override
    public String visitGroupingExpr(Expr.Grouping expr) {
        return expr.expression.accept(this);
    }

    @Override
    public String visitLiteralExpr(Expr.Literal expr) {
        return String.valueOf(expr.value);
    }

    @Override
    public String visitUnaryExpr(Expr.Unary expr) {
        String operator = expr.operator.lexeme;
        if (expr.operator.type == TokenType.MINUS) {
      // to tell apart unary and binary "-" operator
      operator = "~";
    }
        return expr.right.accept(this) + " "
             + operator;
    }

    @Override
    public String visitVariableExpr(Expr.Variable expr) {
        return expr.name.lexeme;
    }

    @Override
    public String visitAssignExpr(Expr.Assign expr) {
        return expr.value.accept(this);
    }

    @Override
    public String visitLogicalExpr(Expr.Logical expr) {
        return expr.left.accept(this) + " "
             + expr.right.accept(this) + " "
             + expr.operator.lexeme;
    }

    @Override
    public String visitCallExpr(Expr.Call expr) {
        StringBuilder result = new StringBuilder();

        result.append(expr.callee.accept(this));

        for (Expr argument : expr.arguments) {
            result.append(" ");
            result.append(argument.accept(this));
        }

        result.append(" call");

        return result.toString();
    }

    @Override
    public String visitGetExpr(Expr.Get expr) {
        return expr.object.accept(this) + " " + expr.name.lexeme;
    }

    @Override
    public String visitSetExpr(Expr.Set expr) {
        return expr.value.accept(this) + " "
             + expr.object.accept(this) + " "
             + expr.name.lexeme;
    }

    @Override
    public String visitThisExpr(Expr.This expr) {
        return "this";
    }

    @Override
    public String visitSuperExpr(Expr.Super expr) {
        return "super." + expr.method.lexeme;
    }

    // test RpnPrinter. this main class is taken from https://github.com/munificent/craftinginterpreters to test my own implementation and compare
    // i added test for visit call expr
    public static void main(String[] args) {
    Expr expression = new Expr.Binary(
        new Expr.Unary(
            new Token(TokenType.MINUS, "-", null, 1),
            new Expr.Literal(123)),
        new Token(TokenType.STAR, "*", null, 1),
        new Expr.Grouping(
            new Expr.Literal("str")));
    
        // add to test call expr
        Expr call = new Expr.Call(
        new Expr.Variable(
            new Token(TokenType.IDENTIFIER, "func", null, 1)
        ),
        new Token(TokenType.RIGHT_PAREN, ")", null, 1),
        Arrays.asList(
            new Expr.Literal(1),
            new Expr.Literal(2)
        )
    );

    System.out.println(new RpnPrinter().print(expression));
    System.out.println(new RpnPrinter().print(call));
  }
}

