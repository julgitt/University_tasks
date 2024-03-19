using System;

namespace New {
    class ReportPrinter {
    	private DataRetriever dataRetriever;
    	private DocumentFormatter documentFormatter;
    	
    	public ReportPrinter() {
        this.dataRetriever = new DataRetriever();
        this.documentFormatter = new DocumentFormatter();
    }
        public void PrintReport() {
            string data = dataRetriever.GetData();
            documentFormatter.FormatDocument();
            Console.WriteLine("Printing report: " + data);
        }
    }

    class DataRetriever {
        public string GetData() {
            Console.WriteLine("Retrieving data...");
            return "example data";
        }
    }

    class DocumentFormatter {
        public void FormatDocument() {
            Console.WriteLine("Formatting document...");
        }
    }
}
