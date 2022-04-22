package com.company;

public class Main {

        public static void main(String[] args) {
            Expression expr = new Subtract(new Const(4), new Variable("x"));

            System.out.println(expr + " = " + expr.Evaluate());
            Expression expr2 = new Subtract(new Add(new Add(new Const(5), new Const(5)), new Variable("x")), new Variable("x"));
            System.out.println(expr2 + " = " + expr2.Evaluate());
            Expression expr3 = new Subtract(new Add(new Const(5), new Const(5)), new Variable("x"));
            System.out.println(expr3 + " = " + expr3.Evaluate());
        }
}

