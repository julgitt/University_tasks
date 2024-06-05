using System;

namespace Zad2 {
    public interface IShape {
        public int GetArea();
    }

    public class Rectangle : IShape {
        public virtual int Width { get; set; }
        public virtual int Height { get; set; }

        public Rectangle(int width, int height)
        {
            Width = width;
            Height = height;
        }

        public int GetArea() {
            return Width * Height;
        }
    }

    public class Square : IShape {
        public int SideLength {get; set;}

        public Square(int sideLength)
        {
            SideLength = sideLength;
        }


        public int GetArea() {
            return SideLength * SideLength;
        }
    }


    public class AreaCalculator {
        public int CalculateArea(IShape shape) {
            return shape.GetArea();
        }
    }
}