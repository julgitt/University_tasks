
public class Program {
	public static void Main() {
		int w = 4, h = 5;

		Old.Rectangle rect = new Old.Square() { Width = w, Height = h };

		Old.AreaCalculator calc = new Old.AreaCalculator();

		Console.WriteLine(
			"prostokąt o wymiarach {0} na {1} ma pole {2}",
			w, h, calc.CalculateArea(rect) 
		);


        // new

        New.Shape rect2 = new New.Rectangle() { Width = w, Height = h };
        New.Shape square = new New.Square() { SideLength = w };

        New.AreaCalculator calc2 = new New.AreaCalculator();

        Console.WriteLine(
            "prostokąt o wymiarach {0} na {1} ma pole {2}",
            w, h, calc2.CalculateArea(rect2)
        );

        Console.WriteLine(
            "Kwadrat o wymiarach {0} na {0} ma pole {1}",
            w, calc2.CalculateArea(square)
        );
	}
}