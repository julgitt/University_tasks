using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.ServiceProcess;
using System.Text;
using System.Threading.Tasks;
using System.Timers;

namespace AppLogger
{
    public partial class ApplicationLoggerService : ServiceBase
    {
        private Timer timer;

        public ApplicationLoggerService()
        {
            InitializeComponent();
        }

        protected override void OnStart(string[] args)
        {
            // Inicjalizacja i uruchomienie timera
            timer = new Timer();
            timer.Interval = 60000; // 1 minuta
            timer.Elapsed += TimerElapsed;
            timer.Start();
        }

        protected override void OnStop()
        {
            // Zatrzymanie timera
            timer.Stop();
            timer.Dispose();
        }

        private void TimerElapsed(object sender, ElapsedEventArgs e)
        {
            // Pobranie listy uruchomionych procesów
            var processes = Process.GetProcesses();

            // Ścieżka do pliku tekstowego, gdzie zapisywana będzie lista
            var filePath = @"C:\Logs\ApplicationList.txt";

            // Zapis listy uruchomionych procesów do pliku tekstowego
            using (var writer = new StreamWriter(filePath, true)) // lub false jesli chcemy nadpisywac a nie dopisywac
            {
                writer.WriteLine($"[{DateTime.Now}]");

                foreach (var process in processes)
                {
                    writer.WriteLine($"{process.ProcessName} (ID: {process.Id})");
                }

                writer.WriteLine();
            }
        }
    }
}
