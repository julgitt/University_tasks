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

namespace Task1List8
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void btnDecline(object sender, RoutedEventArgs e)
        {
            // Close the application
            Application.Current.Shutdown();
        }

        private void btnAccept(object sender, RoutedEventArgs e)
        {
            bool allBoxesFilled = true;
            string text_parameter = "";
            foreach (UIElement element in GetAllElements(this))
            {
                if (element is TextBox textBox)
                {
                    if (string.IsNullOrEmpty(textBox.Text))
                    {
                        allBoxesFilled = false;
                        break;
                    }
                    text_parameter += textBox.Text + "\n";
                }
                else if (element is CheckBox checkbox)
                {
                    if (checkbox.IsChecked == true)
                    {
                        text_parameter += checkbox.Content + "\n";
                    }
                }
                else if (element is ComboBox combobox)
                {
                    if (combobox.SelectedIndex == -1)
                    {
                        allBoxesFilled = false;
                        break;
                    }
                    text_parameter += combobox.Text + "\n";
                }
            }

            if (allBoxesFilled)
            {
                Window1 messageWindow = new Window1(text_parameter); 
                messageWindow.ShowDialog(); // Show the new window
                if (messageWindow.DialogResult == true)
                {
                    this.Close();
                }
            }
        }

        private IEnumerable<UIElement> GetAllElements(DependencyObject parent)
        {
            var children = new List<UIElement>();
            int count = VisualTreeHelper.GetChildrenCount(parent);

            for (int i = 0; i < count; i++)
            {
                var child = VisualTreeHelper.GetChild(parent, i);

                if (child is UIElement element)
                {
                    children.Add(element);
                    children.AddRange(GetAllElements(child));
                }
            }

            return children;
        }
    }
}
