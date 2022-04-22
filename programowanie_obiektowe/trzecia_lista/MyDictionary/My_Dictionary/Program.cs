using System;
using ClassLibrary;
namespace MyDictionary
{
    class Program
    {
        static void Main(string[] args)
        {
            MyDictionary<string, int> dictionary = new MyDictionary<string, int>();
            dictionary.Insert("a", 1);
            dictionary.Insert("b", 2);
            Console.WriteLine(dictionary.Find_element("a"));
            Console.WriteLine(dictionary.Find_element("b"));
            dictionary.Del("b");
            Console.WriteLine(dictionary.Find_element("a"));
        }
    }
}
