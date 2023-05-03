/*  Napisać program, który wyznacza zbiór wszystkich liczb natualnych 1 a 100000, które
są podzielne zarówno przez każdą ze swoich cyfr z osobna jak i przez sumę  swoich cyfr. */

using System;
using System.Collections.Generic;

namespace Task1_List1
{
    /// <summary>
    /// Solution
    /// </summary>

    public class Program
    {
    
        public static void Main(string[] args)
        {
            int last = 100000;
            int sum;
            int j;
            for (int i = 1; i < last; i++)
            {
                sum = 0;
                j = i;
                while (j % 10 > 0)
                {
                    if (i % (j % 10) != 0)
                    {
                        break;
                    }
                    sum += j % 10;
                    j /= 10;
                }
                if (sum != 0 && i % sum == 0 && j == 0)
                {
                    Console.WriteLine(i);
                }
            }
        }
    }

}
