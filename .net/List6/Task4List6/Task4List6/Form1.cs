using System.Configuration;

namespace Task4List6
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            // Odczytujemy wartoœci z pliku konfiguracyjnego
            string myString = ConfigurationManager.AppSettings["MyString"];
            int myInt = int.Parse(ConfigurationManager.AppSettings["MyInt"]);
            bool myBool = bool.Parse(ConfigurationManager.AppSettings["MyBool"]);

            // Zmieniamy wartoœæ zmiennej na "Hello User"
            ConfigurationManager.AppSettings.Set("MyString", "Hello User");

            // Odczytujemy zmienion¹ wartoœæ zmiennej z pliku konfiguracyjnego
            string modifiedMyString = ConfigurationManager.AppSettings["MyString"];

            // Wyœwietlamy odczytane wartoœci w interfejsie u¿ytkownika
            MessageBox.Show($"MyString: {myString}\nMyInt: {myInt}\nMyBool: {myBool}\nModified MyString: {modifiedMyString}");
        }
    }
}