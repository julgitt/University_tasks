/*  Napisać program, który wyznacza zbiór wszystkich liczb natualnych 1 a 100000, które
są podzielne zarówno przez każdą ze swoich cyfr z osobna jak i przez sumę  swoich cyfr. */

using System;
using System.Collections.Generic;
using ClassLibrary1;
using ClassLibrary2;

namespace Console_App_2
{
    /// <summary>
    /// Solution - Second Class
    /// </summary>

    public class Program
    {
        /// <summary>
        /// Main Function
        /// </summary>
        public static void Main(string[] args)
        {
            // we are in 'A' project now
            Console.WriteLine('A');

            // Library class new objects
            Class1 age = new Class1();
            Class2 welcome = new Class2();
           
            // get name and print welcome text from 2 class library method
            string name = "" + Console.ReadLine();
            Console.WriteLine(welcome.exampleMethod(name));
            // print age by 1 class library method
            Console.WriteLine(age.exampleMethod(18));

            // wait for input, so the window doesn't close immediately after the print
            Console.ReadLine();
        }
    }

}
