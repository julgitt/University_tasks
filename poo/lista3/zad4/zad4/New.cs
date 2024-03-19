using System;

namespace New {
    public abstract class Shape {
        public abstract int GetArea();
    }

    public class Rectangle : Shape {
        public virtual int Width {get; set;}
        public virtual int Height {get; set;}

        public override int GetArea() {
            return Width * Height;
        }
    }

    public class Square : Shape {
        public int SideLength {get; set;}

        public override int GetArea() {
            return SideLength * SideLength;
        }
    }


    public class AreaCalculator {
        public int CalculateArea(Shape shape) {
            return shape.GetArea();
        }
    }
}