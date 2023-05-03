using System;

namespace Task5List4
{
    class Program
    {
        static void Main(string[] args)
        {
            var daneOsobowe = File.ReadAllLines("daneOsobowe.txt")
             .Select(line => line.Split(' ', StringSplitOptions.RemoveEmptyEntries))
             .Select(parts => new
             {
                 Name = parts[0],
                 Surname = parts[1],
                 PESEL = parts[2]
             });

            var daneKredytowe = File.ReadAllLines("daneKredytowe.txt")
                .Select(line => line.Split(' ', StringSplitOptions.RemoveEmptyEntries))
                .Select(parts => new
                {
                    PESEL = parts[0],
                    AccountNumber = parts[1]
                });

            var result = from person in daneOsobowe
                        join creditInfo in daneKredytowe on person.PESEL equals creditInfo.PESEL
                        select new
                        {
                            person.Name,
                            person.Surname,
                            person.PESEL,
                            creditInfo.AccountNumber
                        };

            foreach (var record in result)
            {
                Console.WriteLine($"Imię: {record.Name}");
                Console.WriteLine($"Nazwisko: {record.Surname}");
                Console.WriteLine($"PESEL: {record.PESEL}");
                Console.WriteLine($"Numer konta: {record.AccountNumber}");
                Console.WriteLine();
            }
        }
    }
}