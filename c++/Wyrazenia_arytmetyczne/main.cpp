#include "classes.h"
#include <iomanip>

int main() {
    Variable::add_Variable("x", 4.0);
    Variable::add_Variable("y", 2.0);

    //pi - (2 + x * 7)
    Expression *w = new Subtraction(
            new pi(),
            new Addition(
                    new Number(2.0),
                    new Multiplication(
                            new Variable("x"),
                            new Number(7.0)
                    )
            ));
    //((x-1)*x)/2
    Expression *w1 = new Division(
            new Multiplication(
                    new Subtraction(
                            new Variable("x"),
                            new Number(1)),
                    new Variable("x")),
            new Number(2));

    //(3+5)/(2+x*7)
    Expression *w2 = new Division(
            new Addition(
                    new Number(3),
                    new Number(5)),
            new Addition(
                    new Number(2),
                    new Multiplication(
                            new Variable("x"),
                            new Number(7))));
    //2+x*7-(y*3+5)
    Expression *w3 = new Subtraction(
            new Addition(
                    new Number(2),
                    new Multiplication(
                            new Variable("x"),
                            new Number(7))),
            new Addition(
                    new Multiplication(
                            new Variable("y"),
                            new Number(3)),
                    new Number(5)));

    //cos((x+1)*pi)/e^x^2 = -1.12535e-07
    Expression *w4 = new Division(
            new Cosinus(
                    new Multiplication(
                            new Addition(
                                    new Variable("x"),
                                    new Number(1)),
                            new pi())),
            new exponential_function(
                    new Exponentiation(
                            new Variable("x"),
                            new Number(2))));


    //cout.precision(3);
    cout << w->to_string() << " = " << w->Evaluate() << endl;
    cout << w1->to_string() << " = " << w1->Evaluate() << endl;
    cout << w2->to_string() << " = " << w2->Evaluate() << endl;
    cout << w3->to_string() << " = " << w3->Evaluate() << endl;
    cout << w4->to_string() << " = " << w4->Evaluate() << endl;

    for (double i = 0.0; i <= 1.0; i += 0.1) {
        Variable::modify_Variable("x", i);
        for (double j = 0.0; j <= 1.0; j += 0.1) {
            Variable::modify_Variable("y", j);
            cout << "\nx = " << setprecision(3) << i << ", y = " << j << endl << w3->to_string() << " = "
                 << setprecision(10) << w3->Evaluate() << endl << endl;
        }
    }
}
