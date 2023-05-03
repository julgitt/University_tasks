using System;

namespace Task3List4
{
    class Program
    {
        static void Main(string[] args)
        {
            // string[] surnames = { "Kowalski", "Malinowski", "Krasicki", "Abacki" };
            string[] surnames = File.ReadAllLines("surnames.txt");
            var firstLetters = surnames
                .Where(surname => !string.IsNullOrEmpty(surname)) // filtorwanie pustych nazwisk
                .GroupBy(surname => surname[0]) // grupowanie po pierwszej literze
                .OrderBy(group => group.Key) // sortowanie grup po pierwszej literze
                .Select(group => group.Key); // wybór pierwszej litery z każdej grupy

            foreach (var letter in firstLetters)
            {
                Console.WriteLine(letter);
            }
        }
    }
}