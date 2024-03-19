public class Program {
    private static void Main() {
        var oldPrinter = new Old.ReportPrinter();
        var newPrinter = new New.ReportPrinter();

        Console.WriteLine("Przed:");
        oldPrinter.PrintReport();

        Console.WriteLine();

        Console.WriteLine("Po:");
        newPrinter.PrintReport();
    }
}
