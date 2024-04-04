using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad2
{
    class Program
    {
        private static void Main(string[] args)
        {
            FileStream fileToWrite = File.Create("./example.txt");
            CaesarStream caeToWrite = new CaesarStream(fileToWrite, 5);
            var buff = new byte[] { 1, 3, 5, 7 };
            caeToWrite.Write(buff, 0, 4);
            caeToWrite.Close();
            fileToWrite.Close();
            FileStream fileToRead = File.Open("./example.txt", FileMode.Open);
            CaesarStream caeToRead = new CaesarStream(fileToRead, -5);
            // -5 znosi 5
            caeToRead.Read(buff, 0, 4); 
            Console.WriteLine("Zawartosc:");
            Console.WriteLine(buff.ToString());
            caeToRead.Close();
            fileToRead.Close();
        }
    }
}
