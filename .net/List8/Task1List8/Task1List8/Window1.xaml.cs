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
using System.Windows.Shapes;
using static System.Net.Mime.MediaTypeNames;

namespace Task1List8
{
    /// <summary>
    /// Interaction logic for Window1.xaml
    /// </summary>
    public partial class Window1 : Window
    {
        private string textParameter { get; set; }
        public Window1(string text)
        {
            this.textParameter = text;
            InitializeComponent();
            this.Label.Content = this.textParameter;
        }

        private void btnClick(object sender, EventArgs e)
        {
            this.DialogResult = true;
            this.Close();
        }
    }
}
