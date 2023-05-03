using System;
using System.IO;
using System.Linq;

namespace Task4List4
{
    class Program
    {
        public static void Main(string[] args)
        {
            string folderPath = "dir";

            // Directory.GetFiles zwraca listę ścieżek do plików znajdujących się w folderze folderPath,
            // włącznie z plikami w podfolderach (SearchOption.AllDirectories).

            // Aggregate - dodaje do siebie dlugosci plikow:
            // 0L - wartosc poczatkowa akumulatora acc przechowujacego sume
            // do akumulatora dodajemy dlugosc pliku
            // uzyskana dzieki funkcji FileInfo("path").Length

            long totalLength = Directory.GetFiles(folderPath, "*", SearchOption.AllDirectories)
                .Aggregate(0L, (acc, filePath) => acc + new FileInfo(filePath).Length);

            Console.WriteLine(totalLength.ToString());
        }
    }
}