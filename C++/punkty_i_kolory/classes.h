
#ifndef QUEUE_CLASSES_H
#define QUEUE_CLASSES_H
#include <iostream>
#include <string>
#include <cmath>
#include <initializer_list>
using namespace std;

class Color {
private:
    int r,g,b;

public:
    //constructors
    Color ();
    Color (int a, int b, int c);

    // Setters
    void SetColor(int r, int g, int b);
    void setRed(int r);
    void setGreen(int g);
    void setBlue(int b);

    // Getters
    int getRed() const;
    int getGreen() const;
    int getBlue() const;

    void Darken(int value);
    void Brighten(int value);

    static Color Sum(Color color1, Color color2);
};

class Transparent : public Color{
    int transparency;
public:
    //constructors
    Transparent ();
    Transparent (int t, int r, int g, int b);
};

class Named_Color : public Transparent{
    string name;
public:
    //constructors
    Named_Color ();
    Named_Color (const string& name,int t, int r, int g, int b);

    static bool containsOnlyLetters(string const &str);
};

class Point {
protected:
    double x,y;
    static int red, green, blue, counter;

public:
    //constructors
    Point ();
    Point (double x, double y);

    double get_x() const;
    double get_y() const;
    double Distance(Point point) const;
    //wspolliniowe
    static bool Collinearity (Point point1, Point point2,Point point3);
};
class Named_Point : public virtual Point{
private:
    string name;

public:
    //constructors
    Named_Point ();
    Named_Point (const string& name,double x, double y);
    static bool containsLettersandNumers (string const &str);
    string get_name() const;
};

class Colored_Point : public virtual Point{
private:
    Transparent color;

public:
    //constructors
    Colored_Point ();
    Colored_Point (Transparent color,double x, double y);
};

class Colored_Named_Point : public Colored_Point, public Named_Point{
public:
    Colored_Named_Point ();
    Colored_Named_Point (Transparent color, const string& name, double x, double y);
};

class vector2d{
public:
    double x;
    double y;
    vector2d();
    vector2d(double x,double y);
};
class vector3d{
public:
    double x;
    double y;
    double z;
    vector3d();
    vector3d(double x,double y, double z);
};

class Point2d : public Point{
public:
    Point2d ();
    Point2d (double x, double y);
    void transposition(vector2d v);
};

class Point3d : public Point2d{
protected:
    using Point2d::x, Point2d::y;
    double z;
public:
    Point3d ();
    Point3d (double x, double y, double z);
    double get_z() const;
    void transposition(vector3d v);
};
#endif //QUEUE_CLASSES_H
