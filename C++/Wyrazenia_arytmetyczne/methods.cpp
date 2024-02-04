#include "classes.h"
//___________________________________________________
//                    EXPRESSION
//___________________________________________________

Expression::Expression(Expression *left, Expression *right) {
    this->left = left;
    this->right = right;
    priority = 10;
}

double Expression::Evaluate() {
    return 0;
}

string Expression::to_string() {
    return ::to_string(Evaluate());
}

//___________________________________________________
//                   NUMBER
//___________________________________________________

Number::Number(double value):Expression(nullptr, nullptr) {
    this->value = value;
}

double Number::Evaluate() {
    return value;
}

string Number::to_string() {
    string str = ::to_string(Evaluate());
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    str.erase(str.find_last_not_of('.') + 1, std::string::npos);
    return str;
}


//___________________________________________________
//                   VARIABLE
//___________________________________________________

Variable::Variable(const string& name) : Expression(nullptr, nullptr) {
    this->name = name;
    set_of_variables = {};

}

void Variable::add_Variable(const string& name, double value) {
    if (std::find(set_of_variables.begin(), set_of_variables.end(), make_pair(name, value)) != set_of_variables.end()) {
        throw invalid_argument("There is already such a variable in the set, use \"modify_Variable\" instead.");
    }
    set_of_variables.emplace_back(name, value);
}

void Variable::delete_Variable(const string& name) {
    int i = 0;
    while (i < set_of_variables.capacity()) {
        if (set_of_variables[i].first == name) {
            set_of_variables.erase(set_of_variables.begin() + i);
            return;
        }
        i++;
    }
    throw invalid_argument("There is no such a variable in the set.");
}

void Variable::modify_Variable(const string& name, double value) {
    int i = 0;
    while (i < set_of_variables.capacity()) {
        if (set_of_variables[i].first == name) {
            set_of_variables[i].second = value;
            return;
        }
        i++;
    }

    throw invalid_argument("There is no such a variable in the set. Create one by using \"add_Variable\".");
}

double Variable::Evaluate() {

    int i = 0;
    while (i < set_of_variables.capacity()) {
        if (set_of_variables[i].first == name) {
            return set_of_variables[i].second;
        }
        i++;
    }
    throw invalid_argument("There is no such a variable in the set. Create one by using \"add_Variable\".");
}

string Variable::to_string() {
    return name;
}

//___________________________________________________
//                   CONSTS
//___________________________________________________

pi::pi() : Expression(nullptr, nullptr)  {}

double pi::Evaluate() {
    return M_PI;
}

string pi::to_string() {
    return "pi";
}

e::e() : Expression(nullptr, nullptr)  {}

double e::Evaluate() {
    return M_E;
}

string e::to_string() {
    return "e";
}

fi::fi() : Expression(nullptr, nullptr)  {}

double fi::Evaluate() {
    return 1.6180339887;
}

string fi::to_string() {
    return "e";
}

//___________________________________________________
//                   UNARY OPERATORS
//___________________________________________________

Unary_Operator::Unary_Operator (Expression *exp): Expression(exp, nullptr){}

Sinus::Sinus (Expression *exp): Unary_Operator(exp){}

double Sinus::Evaluate() {
    return sin(left->Evaluate());
}

string Sinus::to_string() {
    return "sin(" + left->to_string() + ")";
}

Cosinus::Cosinus (Expression *exp): Unary_Operator(exp){}

double Cosinus::Evaluate() {
    return cos(left->Evaluate());
}

string Cosinus::to_string() {
    return "cos(" + left->to_string() + ")";
}

Absolute::Absolute(Expression *exp): Unary_Operator(exp){}

double Absolute::Evaluate() {
    return abs(left->Evaluate());
}

string Absolute::to_string() {
    return "|" + left->to_string() + "|";
}

Reciprocal::Reciprocal(Expression *exp): Unary_Operator(exp) {
    priority = 9;
}//odwrotnosc

double Reciprocal::Evaluate() {
    return 1.0 / (left->Evaluate());
}

string Reciprocal::to_string() {
    string n;
    if (left->priority < this->priority) n = "(" + left->to_string() + ")";
    else n = left->to_string();

    return "1 / " + n;
}

Inverse::Inverse(Expression *exp): Unary_Operator(exp) { //przeciwna
    priority = 8;
}//odwrotnosc

double Inverse::Evaluate() {
    return -(left->Evaluate());
}

string Inverse::to_string() {
    string n;
    if (left->priority < this->priority) n = "(" + left->to_string() + ")";
    else n = left->to_string();

    return "-" + n;
}

ln::ln(Expression *exp): Unary_Operator(exp){}

double ln::Evaluate() {
    return log(left->Evaluate());
}

string ln::to_string() {
    return "ln(" + left->to_string() + ")";
}

exponential_function::exponential_function(Expression *exp): Unary_Operator(exp){
    priority = 9;
}

double exponential_function::Evaluate() {
    return (new Exponentiation(new e(),left))->Evaluate();
}

string exponential_function::to_string() {
    string n;
    if (left->priority < this->priority) n = "(" + left->to_string() + ")";
    else n = left->to_string();

    return "e^" + n;
}

//___________________________________________________
//                   BINARY OPERATORS
//___________________________________________________
Binary_Operator::Binary_Operator (Expression *first, Expression *second): Expression(first, second){}

Addition::Addition (Expression *first, Expression *second): Binary_Operator(first,second) {
    priority = 5;
}

double Addition::Evaluate() {
    return (left->Evaluate()) + (right->Evaluate());
}

string Addition::to_string() {
    return left->to_string() + " + " + right->to_string();
}

Subtraction::Subtraction (Expression *first, Expression *second): Binary_Operator(first,second) {
    priority = 6;
}

double Subtraction::Evaluate() {
    return (left->Evaluate()) - (right->Evaluate());
}

string Subtraction::to_string() {
    string r;
    if (right->priority < this->priority) r = "(" + right->to_string() + ")";
    else r = right->to_string();

    return left->to_string() + " - " + r;
}

Multiplication::Multiplication (Expression *first, Expression *second): Binary_Operator(first,second) {
    priority = 7;
}

double Multiplication::Evaluate() {
    return (left->Evaluate()) * (right->Evaluate());
}

string Multiplication::to_string() {
    string l, r;
    if (left->priority < this->priority) l = "(" + left->to_string() + ")";
    else l = left->to_string();

    if (right->priority < this->priority) r = "(" + right->to_string() + ")";
    else r = right->to_string();

    return l + " * " + r;
}

Division::Division (Expression *first, Expression *second): Binary_Operator(first,second) {
    priority = 7;
}

double Division::Evaluate() {
    return (left->Evaluate()) / (right->Evaluate());
}

string Division::to_string() {
    string l, r;
    if (left->priority < this->priority) l = "(" + left->to_string() + ")";
    else l = left->to_string();

    if (right->priority < this->priority) r = "(" + right->to_string() + ")";
    else r = right->to_string();

    return l + " / " + r;
}

Logarithm::Logarithm (Expression *first, Expression *second): Binary_Operator(first,second){}

double Logarithm::Evaluate() {
    return (log(left->Evaluate())) / (log(right->Evaluate()));
}

string Logarithm::to_string() {

    return " log " + left->to_string() + "(" + right->to_string() + ")";
}

Modulo::Modulo (Expression *first, Expression *second): Binary_Operator(first,second){}

double Modulo::Evaluate() {
    return fmod(left->Evaluate(), right->Evaluate());
}

string Modulo::to_string() {

    return left->to_string() + " mod " + right->to_string();
}

Exponentiation::Exponentiation (Expression *first, Expression *second): Binary_Operator(first,second) {
    priority = 9;
}

double Exponentiation::Evaluate() {
    return pow(left->Evaluate(), right->Evaluate());
}

string Exponentiation::to_string() {
    string l, r;
    if (left->priority < this->priority) l = "(" + left->to_string() + ")";
    else l = left->to_string();

    if (right->priority < this->priority) r = "(" + right->to_string() + ")";
    else r = right->to_string();

    return l + "^" + r;
}