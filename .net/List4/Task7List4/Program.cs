using System;
using System.Diagnostics;

namespace Task7List4
{
    class Program
    {
        static void Main(string[] args)
        {

            var l = new[] { new { a = 1, b = "ff" } }.ToList();

            l.Add(new { a = 2, b = "aa" });

            // l.Add(new { c = 3, b = "aa" }); nie pozwoli nam dodac elementu ktory nie zgadza sie z typem pierwszego elementu

            foreach (var element in l)
            {
                var properties = element.GetType().GetProperties();
                foreach (var property in properties)
                {
                    var value = property.GetValue(element);
                    Console.WriteLine($"{property.Name}: {value}");
                }
            }
        }
    }
}