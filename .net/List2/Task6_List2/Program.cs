using System;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Runtime.ExceptionServices;

namespace Task6_List2
{
    public delegate void PropertyChangedDelegate(object source, string propertyName, object propertyValue);
    public class Person
    {
        // Declare the event.
        public event PropertyChangedDelegate PropertyChangedHandler;

        private string _name;
        private string _surname;

        public string Name
        {
            get { return _name; }
            set
            {
                if (_name != value)
                {
                    _name = value;
                    if (PropertyChangedHandler != null)
                        PropertyChangedHandler(this, nameof(_name), value);
                }
            }
        }

        public string Surname
        {
            get { return _surname; }
            set
            {
                if (_surname != value)
                {
                    _surname = value;
                    if (PropertyChangedHandler != null)
                        PropertyChangedHandler(this, nameof(_surname), value);
                }
            }
        }
        public Person()
        {
            _name = "Jan";
            _surname = "Kowalski";
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Person person = new Person();
            person.PropertyChangedHandler += OnPropertyChanged;
            person.PropertyChangedHandler += (s, p, pv) => { };
            person.Name = "Stefan";
            Console.ReadLine();
        }
        public static void OnPropertyChanged(object source, string propertyName, object propertyValue)
        {
            Console.WriteLine("właściwość {0}, nowa wartość {1}", propertyName, propertyValue);
        }
    }
    
}