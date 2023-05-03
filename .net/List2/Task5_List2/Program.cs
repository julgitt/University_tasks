using System;

namespace Task5_List2
{
    public class Example
    {
        public int auto_implemented_prop_field { get; set; }
        private string _backing_field;

        public string Backing_filed_property
        {
            get { return _backing_field; }
            set { _backing_field = value; }
        }
        public Example()
        {
            _backing_field = "init";
        }
    }

    class Program
    {
        public static void Main(string[] args)
        {
            Example new_object = new Example();
            new_object.auto_implemented_prop_field = 2;
            new_object.Backing_filed_property = "new value";
            Console.WriteLine("getting from auto-implemented property: " + new_object.auto_implemented_prop_field);
            Console.WriteLine("getting from backing-field property: " + new_object.Backing_filed_property);
        }
    }
}