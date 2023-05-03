using System;
using System.Text.RegularExpressions;

namespace Task1List4
{
    public static class StringExtensions
    {
        public static bool IsPalindrome(this string input)
        {
            // usuwamy biale znaki i zmieniamy wszystkie litery na male
            string cleanString = Regex.Replace(input, @"[\W_]", "").ToLower();

            // zmieniamy na tablice charow i odwracamy
            char[] charArray = cleanString.ToCharArray();
            Array.Reverse(charArray);
            string reversedString = new string(charArray);

            // patrzymy czy sa rowne
            return cleanString.Equals(reversedString);
        }
    }

    class Program
    {
       
           
        static void Main(string[] args) 
        {
            string s = "Kobyła ma mały bok.";
            bool ispalindrome = s.IsPalindrome();
            Console.WriteLine(s + ": " + ispalindrome);
            string n = "Kobyła nie ma małego boku.";
            bool notpalindrome = n.IsPalindrome();
            Console.WriteLine(n + ": " + notpalindrome);
        }
    }
}