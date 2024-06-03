using System.Xml;

namespace Template_Method.Handlers
{
    internal class XmlDataAccessHandler : DataAccessHandler
    {
        private XmlDocument xmlDocument;

        protected override void Connect()
        {
            xmlDocument = new XmlDocument();
            Console.WriteLine("Initialized XML handler.");
        }

        protected override object GetData()
        {
            xmlDocument.Load("example.xml");
            Console.WriteLine("XML file loaded.");
            return xmlDocument;
        }

        protected override void ProcessData(object data)
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

        protected override void Close()
        {
            xmlDocument = null;
            Console.WriteLine("XML handler closed.");
        }
    }
}
