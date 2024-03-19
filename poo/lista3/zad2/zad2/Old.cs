using System;

namespace Old {
    public class ReportPrinter {
        public string GetData() {
            Console.WriteLine("Retrieving data...");
            return "some data";
        }

        public void FormatDocument() {
            Console.WriteLine("Formatting document...");
        }

        public void PrintReport() {
            string data = GetData();
            FormatDocument();
            Console.WriteLine("Printing report: " + data);
        }
    }

}


