using System;
using System.Collections.Generic;
using System.Drawing;
using System.Numerics;

namespace Task7_List2
{
    public class Vector {
        public int X { get; set; }
        public int Y { get; set; }

        public static Vector operator -(Vector a, Vector b)
        {
            Vector v = new Vector();
            v.X = a.X - b.X;
            v.Y = a.Y - b.Y;
            return v;
        }
        public static Vector operator +(Vector a, Vector b)
        {
            Vector v = new Vector();
            v.X = a.X + b.X;
            v.Y = a.Y + b.Y;
            return v;
        }
        public static int operator *(Vector a, Vector b)
        {
            int v;
            v = a.X * b.X + a.Y * b.Y;

            return v;
        }
        public static Vector operator *(Vector a, int b)
        {
            Vector v = new Vector();
            v.X = a.X * b;
            v.Y = a.Y * b;
            return v;
        }
        public override string ToString()
        {
            return "(" + X + ", " + Y + ")";
        }
    }

    class Program
    {
        public static void Main(string[] args)
        {
            Vector a = new Vector();
            Vector b = new Vector();
            a.X = 5;
            a.Y = 2;
            b = a * 3;
            Console.WriteLine("a = " + a);
            Console.WriteLine("b = " + b);
            Console.WriteLine("a * b = " + (a * b));
            Console.WriteLine("a + b = " + (a + b));
            Console.WriteLine("a - b = " + (a - b));
            Console.WriteLine("a * 2 = " + (a * 2));
        }
    }
}

