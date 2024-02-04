
#ifndef QUEUE_CLASSES_H
#define QUEUE_CLASSES_H
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <initializer_list>

using namespace std;

class Expression {
protected:
    Expression *left;
    Expression *right;

public:
    int priority;

    Expression(Expression *left, Expression *right);

    virtual double Evaluate();

    virtual string to_string();
};


class Number : public Expression {
private:
    double value;
public:
    explicit Number(double value);

    double Evaluate() override;

    string to_string() override;
};

class Variable : public  Expression {
private:
    inline static vector<pair<string, double>> set_of_variables;
    string name;
public:
    explicit Variable(const string &name);

    static void add_Variable(const string &name, double value);

    static void delete_Variable(const string &name);

    static void modify_Variable(const string &name, double value);

    double Evaluate() override;

    string to_string() override;
};

class pi : public Expression {

public:
    explicit pi();

    string to_string() override;

    double Evaluate() override;
};

class e : public Expression {

public:
    explicit e();

    string to_string() override;

    double Evaluate() override;
};

class fi : public Expression {

public:
    explicit fi();

    string to_string() override;

    double Evaluate() override;
};

class Unary_Operator : public Expression {

public:
    explicit Unary_Operator(Expression *exp);
};

class Sinus : public Unary_Operator {

public:
    explicit Sinus(Expression *exp);

    double Evaluate() override;

    string to_string() override;
};

class Cosinus : public Unary_Operator {

public:
    explicit Cosinus(Expression *exp);

    double Evaluate() override;

    string to_string() override;
};

class Absolute : public Unary_Operator {

public:
    explicit Absolute(Expression *exp);

    double Evaluate() override;

    string to_string() override;
};

class Reciprocal : public Unary_Operator {

public:
    explicit Reciprocal(Expression *exp);

    double Evaluate() override;

    string to_string() override;
};

class Inverse : public Unary_Operator {

public:
    explicit Inverse(Expression *exp);

    double Evaluate() override;

    string to_string() override;
};

class ln : public Unary_Operator {

public:
    explicit ln(Expression *exp);

    double Evaluate() override;

    string to_string() override;
};

class exponential_function : public Unary_Operator {

public:
    explicit exponential_function(Expression *exp);

    double Evaluate() override;

    string to_string() override;
};

class Binary_Operator : public Expression {
protected:
    using Expression::priority;
public:
    explicit Binary_Operator(Expression *first, Expression *second);
};

class Addition : public Binary_Operator {

public:
    explicit Addition(Expression *first, Expression *second);

    double Evaluate() override;

    string to_string() override;
};

class Subtraction : public Binary_Operator {

public:
    explicit Subtraction(Expression *first, Expression *second);

    double Evaluate() override;

    string to_string() override;
};

class Multiplication : public Binary_Operator {

public:
    explicit Multiplication(Expression *first, Expression *second);

    double Evaluate() override;

    string to_string() override;
};

class Division : public Binary_Operator {

public:
    explicit Division(Expression *first, Expression *second);

    double Evaluate() override;

    string to_string() override;
};

class Logarithm : public Binary_Operator {

public:
    explicit Logarithm(Expression *first, Expression *second);

    double Evaluate() override;

    string to_string() override;
};

class Modulo : public Binary_Operator {

public:
    explicit Modulo(Expression *first, Expression *second);

    double Evaluate() override;

    string to_string() override;
};

class Exponentiation : public Binary_Operator {

public:
    explicit Exponentiation(Expression *first, Expression *second);

    double Evaluate() override;

    string to_string() override;
};

#endif //QUEUE_CLASSES_H
