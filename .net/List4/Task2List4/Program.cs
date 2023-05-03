using System;
/*
 * ) Dany jest plik tekstowy zawierający zbiór liczb naturalnych w kolejnych liniach.
Napisać wyrażenie LINQ, które odczyta kolejne liczby z pliku i wypisze tylko liczby większe
niż 100, posortowane malejąco.
from liczba in [liczby]
where ...
orderby ...
select ...
Przeformułować wyrażenie LINQ na ciąg wywołań metod LINQ to Objects:
[liczby].Where( ... ).OrderBy( ... )
Czym różnią się parametry operatorów where/orderby od parametrów funkcji Where,
OrderBy?

 */
namespace Task2List4
{
    class Program
    {
        static void Main(string[] args)
        {
            // operatory LINQ, parametry sa delegatami, dziala na kazdym elemencie osobno
            // przetwarzane w sposob leniwy, tj. elementy sa przetwarzane gdy sa wymagane przez element koncowy
            var wynik2 = from liczba in File.ReadAllLines("text.txt")
                        where int.Parse(liczba) > 100
                        orderby int.Parse(liczba) descending
                        select int.Parse(liczba);

            // funkcje LINQ, przyjmuje lamda-wyrazenie ,
            // jest metoda rozszerzajaca sekwencje, i dziala na rozszerzanej sekwencji
            // nie dziala leniwie, przetwarza sekwencje od razu
            var wynik = File.ReadAllLines("text.txt")
                        .Where(liczba => int.Parse(liczba) > 100)
                        .OrderByDescending(liczba => int.Parse(liczba))
                        .Select(liczba => int.Parse(liczba));

            foreach (var liczba in wynik)
            {
                Console.WriteLine(liczba);
            }
        }
    }
}