using System;

namespace New {
    class ReportPrinter {
        public void PrintReport() {
            var dataGetter = new DataGetter();
            var docFormatter = new DocumentFormatter();
            string data = dataGetter.GetData();
            docFormatter.FormatDocument();
            Console.WriteLine("Printing report: " + data);
        }
    }

    class DataGetter {
        public string GetData() {
            Console.WriteLine("Getting data...");
            return "some data";
        }
    }

    class DocumentFormatter {
        public void FormatDocument() {
            Console.WriteLine("Formatting document...");
        }
    }
}
