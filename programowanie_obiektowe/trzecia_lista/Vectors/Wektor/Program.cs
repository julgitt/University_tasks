using System;
using System.Collections.Generic;
using Vectors_dll;

namespace Wektory
{
    class Program
    {
        static void Main(string[] args)
        {
            Wektor v1 = new Wektor(2, new float[] { 3.0f, -11.0f });
            Wektor v2 = new Wektor(2, new float[] { 0.0f, 4.0f });
            Console.WriteLine(v1.norma());
            Console.WriteLine(v1 * v2);
            Wektor v3 = 3.0f * v1;
            Console.WriteLine(v3.norma());
            v3 = v2 + v1;
            Console.WriteLine(v3.norma());
        }
    }
}
