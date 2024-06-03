using System.Xml;

using StrategyPattern.Strategy;

namespace StrategyPattern.DataAccessStrategies
{
    public class XmlStrategy : IDataStrategy
    {
        private XmlDocument xmlDocument;

        public void Connect()
        {
            xmlDocument = new XmlDocument();
            Console.WriteLine("Initialized XML handler.");
        }

        public object GetData()
        {
            xmlDocument.Load("example.xml");
            Console.WriteLine("XML file loaded.");
            return xmlDocument;
        }

        public void ProcessData(object data)
        {
            XmlDocument document = (XmlDocument)data;
            XmlNode longestNode = null;
            int maxLength = 0;

            foreach (XmlNode node in document.DocumentElement.ChildNodes)
            {
                if (node.Name.Length > maxLength)
                {
                    longestNode = node;
                    maxLength = node.Name.Length;
                }
            }

            Console.WriteLine($"Node with the longest name: {longestNode?.Name ?? "None"}");
        }

        public void Close()
        {
            xmlDocument = null;
            Console.WriteLine("XML handler closed.");
        }
    }
}
