package com.company;

public class Add extends Expression {

    public Add(Expression left, Expression right) {
        super(left, right);
        this.value = Evaluate();
    }

    public int Evaluate() {
        return left.Evaluate() + right.Evaluate();
    }

    public String toString() {
        return "(" + left + "+" + right + ")";
    }
}
