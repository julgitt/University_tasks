using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Task1List6
{
    public partial class Form2 : Form
    {
        private string textParameter { get; set; }
        public Form2(string text)
        {
            this.textParameter = text;
            InitializeComponent();
            this.label_infoUczelnia.Text = this.textParameter;
        }

        private void button_ok_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;
            this.Close();
        }
    }
}
