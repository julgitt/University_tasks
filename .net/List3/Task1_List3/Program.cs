using System;
using System.CodeDom.Compiler;
using System.Text;

namespace Task1_List3
{
    public interface IClassInfo
    {
        string GetClassName();
        string[] GetFieldNames();
        object GetFieldValue(string fieldName);
    }

    public class XMLGenerator
    {
        public string GenerateXML(IClassInfo dataObject)
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("<" + dataObject.GetClassName() + ">\n");
            foreach (string field in dataObject.GetFieldNames())
            {
                sb.Append("\t<" + field + ">");
                sb.Append(dataObject.GetFieldValue(field));
                sb.Append("</" + field + ">\n");
            }
            sb.Append("</" + dataObject.GetClassName() + ">");
            return sb.ToString();
        }
    }
    public class Person : IClassInfo
    {
        public string? Name { get; set; }
        public string? Surname { get; set; }

        public string GetClassName()
        {
            return "Person";

        }

        public string[] GetFieldNames()
        {
            return new[] { "Name", "Surname" };

        }

        public object GetFieldValue(string fieldName)
        {
            switch (fieldName)
            {
                case "Name":
                    return Name;
                case "Surname":
                    return Surname;
                default:
                    return null;
            }
            throw new NotImplementedException();
        }
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
