#include "classes.h"

int main() {
    Color c = Color(3,5,20);
    cout << "First color\nred: " << c.getRed()<< " green: " << c.getGreen() << " blue: " << c.getBlue() << endl;
    c.setRed(30);
    c.Brighten(30);
    cout << endl << "Second color\nred: " << c.getRed()<< " green: " << c.getGreen() << " blue: " << c.getBlue() << endl;

    Color b = Color(90,90,200);
    Color a = Color::Sum (b, c);
    cout << endl << "Third color\nred: " << a.getRed()<< " green: " << a.getGreen() << " blue: " << a.getBlue() << endl;

    Transparent t = Transparent(230,3,5,20);

    Point p1 = Point(-5,-3);
    Point p2 = Point(0,-1);
    Point p3 = Point(10,3);
    Point p4 = Point(11,3);

    cout << endl << "Distance: " << p1.Distance(p2) << endl;
    cout << endl << "collinear points: " << Point::Collinearity(p1, p2, p3) << endl;
    cout << "non-linear points: " <<Point::Collinearity(p1, p2, p4) << endl;

    Colored_Named_Point point = Colored_Named_Point(t, "namedPoint", 30, 10);
    cout << endl << point.get_name() << ": "  << "(" << point.get_x() << "," << point.get_y() << ")" << endl;

    Point3d p3d = Point3d(3,4,5);
    cout << endl << "before transposition: "<< "(" << p3d.get_x() << "," << p3d.get_y() << "," << p3d.get_z() <<")" << endl;
    p3d.transposition( vector3d(3, 4, 5));
    cout << "after transposition: "<< "(" << p3d.get_x() << "," << p3d.get_y() << "," << p3d.get_z() << ")" << endl;
    return 0;
}
