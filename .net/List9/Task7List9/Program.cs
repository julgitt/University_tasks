using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Serilog;

namespace Task7List9
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Log.Logger = new LoggerConfiguration()
               .WriteTo.Console() // Logowanie do konsoli
               .WriteTo.File("log.txt") // Logowanie do pliku
               .CreateLogger();

            // Przykładowe logowanie
            Log.Debug("Wiadomość debugowania");
            Log.Information("Przykładowa informacja");
            Log.Warning("Ostrzeżenie");
            Log.Error("Błąd");

            Log.CloseAndFlush(); // Wymagane, aby zapisać wszystkie logi przed zamknięciem aplikacji
            Console.Read();
        }
    }
}
