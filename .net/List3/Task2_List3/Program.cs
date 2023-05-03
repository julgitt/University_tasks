using System;
using System.Diagnostics.Tracing;
using System.Reflection;
using System.Text;

// 2 i 3 zadanie

namespace Task2_List3
{
    [AttributeUsage(AttributeTargets.Property)]
    public class IgnoreInXML : Attribute
    {
        public bool Info;
        public IgnoreInXML(bool Info) { this.Info = Info; }
    }
    public class XMLGenerator
    {
        public string GenerateXML(object dataObject)
        {
            StringBuilder sb = new StringBuilder();
            Type type = dataObject.GetType();
            sb.Append("<" + type.Name + ">\n");
            PropertyInfo[] properties = type.GetProperties();
            foreach (PropertyInfo property in properties)
            {
                IgnoreInXML? ignore = property.GetCustomAttribute(typeof(IgnoreInXML)) as IgnoreInXML;
                if (ignore is null)
                {
                    sb.Append("\t<" + property.Name + ">");
                    sb.Append(property.GetValue(dataObject));
                    sb.Append("</" + property.Name + ">\n");
                }
            }
            sb.Append("</" + type.Name + ">");
            return sb.ToString();
        }
    }
    public class Person
    {
        public string? Name { get; set; }
        [IgnoreInXML(true)]
        public string? Surname { get; set; }
    }

    class Program
    {
        public static void Main(string[] args) 
        {
            Person person =
            new Person()
            {
                Name = "Jan",
                Surname = "Kowalski"
            };
            XMLGenerator generator = new XMLGenerator();
            string xml = generator.GenerateXML(person);
            Console.WriteLine(xml);
        }
    }
}