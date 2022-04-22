package com.company;

public class Expression {
    Expression left, right;
    int value;

    public Expression(Expression left, Expression right) {
        this.left = left;
        this.right = right;
        value = 0;
    }

    int findVal(String name) {
        return switch (name) {
            case "x" -> 1;
            case "y" -> 2;
            case "z" -> 3;
            default -> -1;
        };
    }

    public int Evaluate() {
        return value;
    }
    public String toString() {
        return "" + value;
    }
}
