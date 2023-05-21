using System;
using System.ComponentModel;
using System.Threading;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace Task3List7
{
    public partial class Form1 : Form
    {
        private BackgroundWorker backgroundWorker;

        public Form1()
        {
            InitializeComponent();

            // Inicjalizacja BackgroundWorker
            backgroundWorker = new BackgroundWorker();
            backgroundWorker.WorkerReportsProgress = true; // W³¹czenie raportowania postêpu
            backgroundWorker.DoWork += BackgroundWorker_DoWork;
            backgroundWorker.ProgressChanged += BackgroundWorker_ProgressChanged;
            backgroundWorker.RunWorkerCompleted += BackgroundWorker_RunWorkerCompleted;
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            // Uruchomienie BackgroundWorker
            backgroundWorker.RunWorkerAsync();
        }

        private void BackgroundWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            // Obliczenia w tle
            int rangeStart = 1;
            int rangeEnd = 1000;
            int primeCount = 0;

            for (int i = rangeStart; i <= rangeEnd; i++)
            {
                if (IsPrime(i))
                {
                    primeCount++;
                }

                // Raportowanie postêpu
                int progressPercentage = (int)((i - rangeStart + 1) / (double)(rangeEnd - rangeStart + 1) * 100);
                if ((i % 100) == 0)
                {
                    backgroundWorker.ReportProgress(progressPercentage);
                }
                Thread.Sleep(1);
            }

            e.Result = primeCount;
        }

        private void BackgroundWorker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            // Aktualizacja paska postêpu w UI
            progressBar.Value = e.ProgressPercentage;
        }

        private void BackgroundWorker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            // Zakoñczenie pracy BackgroundWorker
            if (e.Error != null)
            {
                MessageBox.Show("Wyst¹pi³ b³¹d: " + e.Error.Message);
            }
            else if (e.Cancelled)
            {
                MessageBox.Show("Operacja zosta³a anulowana.");
            }
            else
            {
                int primeCount = (int)e.Result;
                MessageBox.Show("Liczby pierwsze w zakresie: " + primeCount);
            }

            // Resetowanie paska postêpu
            progressBar.Value = 0;
        }

        private bool IsPrime(int number)
        {
            if (number < 2) return false;
            if (number == 2) return true;

            for (int i = 2; i <= Math.Sqrt(number); i++)
            {
                if (number % i == 0)
                {
                    return false;
                }
            }

            return true;
        }
    }
}