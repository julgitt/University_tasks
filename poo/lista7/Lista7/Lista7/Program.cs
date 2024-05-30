using Lista7;
using Lista7.Views;

namespace WindowsFormsApp1
{
    static class Program
    {
        /// <summary>
        /// G³ówny punkt wejœcia dla aplikacji.
        /// </summary>
        [STAThread]
        static void Main()
        {
            MainForm mainForm = new MainForm();
            
            Application.EnableVisualStyles();
            Application.Run(mainForm);
        }
    }
}