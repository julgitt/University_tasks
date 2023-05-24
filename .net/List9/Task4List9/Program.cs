using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Task4List9
{
    internal class Program
    {
        static void Main(string[] args)
        {
            // Lista kultur do obsłużenia
            string[] cultures = { "en-US", "de-DE", "fr-FR", "ru-RU", "ar-SA", "cs-CZ", "pl-PL" };

            foreach (string cultureName in cultures)
            {
                // Utwórz obiekt CultureInfo dla danej kultury
                CultureInfo culture = new CultureInfo(cultureName);

                // Pobierz nazwy miesięcy
                string monthNames = string.Join(", ", culture.DateTimeFormat.MonthNames);

                // Pobierz nazwy dni tygodnia
                string dayNames = string.Join(", ", culture.DateTimeFormat.DayNames);

                // Pobierz bieżącą datę w formacie pełnej daty dla danej kultury
                string currentDate = DateTime.Now.ToString("D", culture);

                // Wyświetl wyniki w oknie informacyjnym
                MessageBox.Show($"Kultura: {cultureName}\n\nPełne nazwy miesięcy:\n{monthNames}\n\nPełne nazwy dni tygodnia:\n{dayNames}\n\nBieżąca data:\n{currentDate}",
                                "Informacja", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }

        }
    }
}
