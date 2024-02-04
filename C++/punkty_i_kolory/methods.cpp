#include "classes.h"

//____________________COLOR_______________________
Color::Color() {
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

Color::Color(int r, int g, int b) {
    if (r > 255 ||  r < 0 || g > 255 ||  g < 0 || b > 255 ||  b < 0)
        throw invalid_argument("Numbers must be between 0 and 255");
    this->r = r;
    this->g = g;
    this->b = b;
}
// Setters
void Color::SetColor(int r, int g, int b) {
    if (r > 255 ||  r < 0 || g > 255 ||  g < 0 || b > 255 ||  b < 0)
        throw invalid_argument("Numbers must be between 0 and 255");
    this->r = r;
    this->g = g;
    this->b = b;
}
void Color::setRed(int r){
    if (r > 255 ||  r < 0)
        throw invalid_argument("Red must be between 0 and 255");
    this->r = r;
}
void Color::setGreen(int g){
    if (g > 255 ||  g < 0)
        throw invalid_argument("Green must be between 0 and 255");
    this->g = g;
}
void Color::setBlue(int b){
    if (b > 255 ||  b < 0)
        throw invalid_argument("Blue must be between 0 and 255");
    this->b = b;
}
// Getters
int Color::getRed() const{
    return this->r;
}
int Color::getGreen() const{
    return this->g;
}
int Color::getBlue() const{
    return this->b;
}

//darken
void Color::Darken(int value) {
    setRed(r - value);
    setGreen(g - value);
    setBlue(b - value);
}

//brighten
void Color::Brighten(int value) {
    setRed(r + value);
    setGreen(g + value);
    setBlue(b + value);
}

//sum
Color Color::Sum(Color color1, Color color2){
    return {(color1.r+color2.r)/2,(color1.g+color2.g)/2,(color1.b+color2.b)/2};
}

//____________________TRANSPARENT COLOR_______________________
Transparent::Transparent () : Color (){
    transparency = 255;
}
Transparent::Transparent (int t, int r, int g, int b) : Color (r, g, b){
    transparency = t;
}

//____________________NAMED COLOR_______________________
Named_Color::Named_Color (): Transparent(){
    name = "";
}
Named_Color::Named_Color (const string& name,int t, int r, int g, int b){
    if (containsOnlyLetters(name))
        this->name = name;
    else
        throw invalid_argument("Name should contain ony letters");
}

bool Named_Color::containsOnlyLetters (string const &str) {
    return str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos;
}

//____________________POINT_______________________
Point::Point (){
    x = 0;
    y = 0;
}
Point::Point (double x, double y){
    this->x = x;
    this->y = y;
}

double Point::Distance(Point point) const{
    return sqrt((x-point.x)*(x-point.x)+(y-point.y)*(y-point.y));
}
bool Point::Collinearity (Point p1, Point p2,Point p3) {
    double det = 0;
    det = p1.x * p2.y + p2.x * p3.y + p3.x * p1.y -
          p3.x * p2.y - p1.x * p3.y - p2.x * p1.y;
    if (det == 0) return true;
    return false;
}
double Point::get_x() const{
    return x;
}

double Point::get_y() const{
    return y;
}

//____________________ NAMED POINT_______________________
Named_Point::Named_Point (): Point(){
    name = "";
}
Named_Point::Named_Point (const string& name, double x, double y) : Point(x,y){
    if (containsLettersandNumers(name))
        this->name = name;
    else
        throw invalid_argument("Name should contain ony letters");
}

bool Named_Point::containsLettersandNumers (string const &str) {
    return (isalpha(str[0])) && (str.find_first_not_of("1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos);
}
string Named_Point::get_name() const{
    return name;
}
//____________________COLORED POINT_______________________

Colored_Point::Colored_Point (): Point(){
    color = Transparent();
}

Colored_Point::Colored_Point (Transparent color, double x, double y) : Point(x,y){
    this->color = color;
}

//____________________COLORED NAMED POINT_______________________

Colored_Named_Point::Colored_Named_Point (): Colored_Point(), Named_Point(){}

Colored_Named_Point::Colored_Named_Point (Transparent color, const string& name, double x, double y) : Colored_Point(color,x,y) , Named_Point(name,x,y), Point(x,y){}

//____________________POINT 2D_______________________

Point2d ::Point2d ():Point(){}

Point2d :: Point2d (double x, double y):Point(x,y){}

void Point2d ::transposition(vector2d v) {
    x +=  v.x;
    y +=  v.y;
}
//__________________POINT 3D___________________________

Point3d::Point3d ():Point2d(){
    z = 0;
}
Point3d::Point3d (double x, double y, double z): Point2d(x,y){
    this->z=z;
}
void Point3d::transposition(vector3d v){
    x += v.x;
    y += v.y;
    z += v.z;
}
double Point3d::get_z() const{
    return z;
}

//________________VECTORS
vector2d::vector2d(){
    x = 0;
    y = 0;
}
vector2d::vector2d(double x,double y){
    this -> x = x;
    this -> y = y;
}

vector3d::vector3d(){
    x = 0;
    y = 0;
    z = 0;
}
vector3d::vector3d(double x,double y, double z){
    this -> x = x;
    this -> y = y;
    this -> z = z;
}