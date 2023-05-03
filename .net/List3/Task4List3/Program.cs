
using System;using System.Collections.Generic;
using System.Runtime.CompilerServices;
using System.Security.Cryptography.X509Certificates;

namespace Task4List3
{
    public delegate bool CustomPredicate<T>(T t);
    public class Person
    {
        public int Age { get; set; }
        public string? Name { get; set; }

        public Person(int age) { Age = age;  Name = "Jan"; }
        public override string ToString()
        {
            return Name + " " + Age.ToString(); 
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            List<int> list = new List<int>() { 6,2,1,3,5,4,3 };
            Console.WriteLine("Oryginalna lista:");
            list.ForEach(i => Console.Write("{0} ", i));

            // zwraca liste elementow spelniajacych dany warunek
            Console.WriteLine("\nFindAll(x => x < 2):");
            var sublist = list.FindAll(x => x < 2);
            sublist.ForEach(i => Console.Write("{0} ", i));

            // sortowanie rosnaco
            Console.WriteLine("\nSort:");
            list.Sort((x, y) => (x > y) ? -1 : ((x == y)?  0 : 1));
            list.ForEach(i => Console.Write("{0} ", i));

            // konwertujemy liste intów na listę osób
            Console.WriteLine("\nConvertAll( x => new Person(x) ): ");
            var convertedList = list.ConvertAll( x => new Person(x) );
            convertedList.ForEach(i => Console.Write("{0} ", i));

            // usuwamy wszystkie 3
            Console.WriteLine("\nRemoveAll(x => x == 3): ");
            list.RemoveAll(x => x == 3);
            list.ForEach(i => Console.Write("{0} ", i.ToString()));
            Console.WriteLine();
        }
    }
}