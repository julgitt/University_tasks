namespace Task1List6
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button_anuluj_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        private void button_akceptuj_Click(object sender, EventArgs e)
        {
            bool allBoxesFilled = true;
            string text_parameter = "";
            foreach (Control control in GetAllControls(this))
            {
                if (control is TextBox textBox)
                {
                    if (string.IsNullOrEmpty(textBox.Text))
                    {
                        allBoxesFilled = false;
                        break;
                    }
                    text_parameter += control.Text + "\n";
                }
                else if (control is CheckBox checkbox)
                {
                    if (checkbox.Checked)
                    {
                        text_parameter += checkbox.Text + "\n";
                    }
                }
                else if (control is ComboBox combobox)
                {
                    if (combobox.SelectedIndex == -1)
                    {
                        allBoxesFilled = false;
                        break;
                    }
                    text_parameter += control.Text + "\n";
                }
            }

            if (allBoxesFilled)
            {
                Form2 form2 = new Form2(text_parameter); // Create a new instance of Form2
                var result = form2.ShowDialog(); // Show the new form
                if (result == DialogResult.OK)
                {
                    this.Close();
                }
            }
        }

   
        private IEnumerable<Control> GetAllControls(Control control)
        {
            var controls = control.Controls.Cast<Control>();

            return controls.SelectMany(ctrl => GetAllControls(ctrl))
                                      .Concat(controls);
        }
    }
}