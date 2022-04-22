package com.company;

public class Variable extends Expression {
    String name;

    Variable(String name) {
        super(null, null);
        this.name = name;
        this.value = findVal(name);
    }
    public String toString() {
        return name;
    }
}
