#include "classes.h"

variable::variable(){
    key = "_";
}
variable::variable(string name) {
    this->key = name;
    this->value = 0;
}
variable::variable(string name, double val){
    this->key = name;
    this->value = val;
}
string variable :: get_key(){
    return key;
}
double variable::get_value() const{
    return value;
}
void variable::set_value(double n){
    value = n;
}