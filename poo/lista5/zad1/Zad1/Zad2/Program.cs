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
            byte[] dataToWrite = { 65, 66, 67, 68, 69 };
            caeToWrite.Write(dataToWrite, 0, dataToWrite.Length);
            caeToWrite.Close();
            fileToWrite.Close();
            FileStream fileToRead = File.Open("./example.txt", FileMode.Open, FileAccess.Read);
            CaesarStream caeToRead = new CaesarStream(fileToRead, -5);
            // -5 znosi 5
            byte[] readBuffer = new byte[1024];
            int bytesRead = caeToRead.Read(readBuffer, 0, readBuffer.Length);
            caeToRead.Close();
            fileToRead.Close();

            Console.WriteLine("Zawartość:");
            for (int i = 0; i < bytesRead; i++)
            {
                Console.Write((char)readBuffer[i] + " ");
            }
            Console.WriteLine();
        }
    }
}
