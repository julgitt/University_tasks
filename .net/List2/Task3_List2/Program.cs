using System;
using System.Reflection;

namespace Task3_List2
{
    //Functions overloading
    class Multiply
    {
        public int a, b;

        public Multiply()
        { 
            Console.WriteLine("konstruktor bez argumentów"); 
        }
        public Multiply(int a) 
        {
            this.a = a;
            Console.WriteLine("konstruktor z 1 argumentem");
        }
        public Multiply(int a, int b) : this(a)
        {
            Console.WriteLine("konstruktor z 2 argumentami");
            this.b = b;
        }
        public double mulDisplay(int one, int two)
        {
            Console.WriteLine("funkcjia z 2 argumentami");
            return one * two;
        }

        public int mulDisplay(int one, int two, int three)
        {
            Console.WriteLine("funkcja z 3 argumentami");
            return (int)mulDisplay(one, two) * three;
        }

        public int mulDisplay(int one, int two, int three, int four)
        {
            Console.WriteLine("funkcja z 4 argumentami");
            return mulDisplay(one,two,three) * four;
        }
    }
    class Program
    {
        public static void Main(string[] args)
        {
            Multiply mult = new Multiply(3, 4);
            Console.WriteLine(mult.mulDisplay(mult.a, mult.b, 5));
        }
    }
}
