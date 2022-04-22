package com.company;

public class Subtract extends Expression {

    public Subtract(Expression minued, Expression subtrahend) {
        super(minued, subtrahend);
        this.value = 0;
    }

    public int Evaluate() {
        return left.Evaluate() - right.Evaluate();
    }

    public String toString() {
        return "(" + left + "-" + right + ")";
    }
}
