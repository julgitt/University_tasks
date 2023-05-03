using System;
namespace Task3List5
{
    class Program
    {
        public static async Task Main(string[] args)
        {
            Console.WriteLine("1");
            await Task.Delay(2000); // (1) Albo Thread.Sleep(2000) ale jest to funkcja blokujaca
            Console.WriteLine("1");
        }
    }
}