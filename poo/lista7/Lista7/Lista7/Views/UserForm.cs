namespace Lista7
{
    public partial class UserForm : Form
    {

        public string? UserName { get; private set; }
        public int Age { get; private set; }

        public UserForm()
        {
            InitializeComponent();
        }

        public UserForm(string name, int age) : this()
        {
            textBox1.Text = name;
            textBox2.Text = age.ToString();
        }

        private void button_cancel_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void button_ok_Click(object sender, EventArgs e)
        {
            UserName = textBox1.Text;
            Age = int.Parse(textBox2.Text);

            DialogResult = DialogResult.OK;
            Close();
        }
    }
}
