public class Program {
    private static void Main() {
        var oldPrinter = new Old.ReportPrinter();
        var newPrinter = new New.ReportPrinter();

        Console.WriteLine("== Test kodu przed zmianami ==");
        oldPrinter.PrintReport();

        Console.WriteLine();

        Console.WriteLine("== Test kodu po zmianach ==");
        newPrinter.PrintReport();
    }
}
