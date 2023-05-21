using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using System.Windows;
using System.Windows.Controls;

namespace TicTacToe
{
    public partial class MainWindow : Window
    {
        private bool isPlayer1Turn = true;
        private Button[,] buttons;

        public MainWindow()
        {
            InitializeComponent();
            buttons = new Button[3, 3]{
                { this.btn1, this.btn2, this.btn3 },
                { this.btn4, this.btn5, this.btn6 },
                { this.btn7, this.btn8, this.btn9 }
            };
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Button button = (Button)sender;

            if (button.Content == null)
            {
                button.Content = isPlayer1Turn ? "X" : "O";
                isPlayer1Turn = !isPlayer1Turn;
                CheckForWin();
            }
        }

        private void CheckForWin()
        {
            // Sprawdź czy któryś z graczy wygrał
            // W którymś rzędzie
            for (int row = 0; row < 3; row++)
            {
                if (buttons[row, 0].Content != null && buttons[row, 0].Content == buttons[row, 1].Content && buttons[row, 1].Content == buttons[row, 2].Content)
                {
                    ShowWinner(buttons[row, 0].Content.ToString());
                    return;
                }
            }

            // W którejś kolumnie
            for (int col = 0; col < 3; col++)
            {
                if (buttons[0, col].Content != null && buttons[0, col].Content == buttons[1, col].Content && buttons[1, col].Content == buttons[2, col].Content)
                {
                    ShowWinner(buttons[0, col].Content.ToString());
                    return;
                }
            }

            // Na przekątnych
            if (buttons[0, 0].Content != null && buttons[0, 0].Content == buttons[1, 1].Content && buttons[1, 1].Content == buttons[2, 2].Content)
            {
                ShowWinner(buttons[0, 0].Content.ToString());
                return;
            }

            if (buttons[0, 2].Content != null && buttons[0, 2].Content == buttons[1, 1].Content && buttons[1, 1].Content == buttons[2, 0].Content)
            {
                ShowWinner(buttons[0, 2].Content.ToString());
                return;
            }

            // Sprawdź czy jest remis
            bool isDraw = true;

            foreach (Button button in buttons)
            {
                // Gra się jeszcze nie skończyła
                if (button.Content == null)
                {
                    isDraw = false;
                    break;
                }
            }

            // Remis
            if (isDraw)
            {
                ShowWinner("Draw");
            }
        }

        private void ShowWinner(string winner)
        {
                string message = "";

                if (winner == "Draw")
                {
                    message = "Remis!";
                }
                else
                {
                    message = "Wygrał gracz: " + winner;
                }

                // Ustawienie informacji o wygranej
                this.txtBlockWinner.Text = message;

                // Wyłączenie możliwości klikania w przyciski
                foreach (Button button in buttons)
                {
                    button.IsEnabled = false;
                }
        }
    }
}