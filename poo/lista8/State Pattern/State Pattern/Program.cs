using StatePattern.Context;

namespace StatePattern
{
    class Program
    {
        static void Main(string[] args)
        {
            CoffeeMachine coffeeMachine = new CoffeeMachine();
            while (Console.ReadLine() == "Start")
            {
                coffeeMachine.Request();  // Włączanie ekspresu
                coffeeMachine.Request();  // Sprawdzanie stanu
                coffeeMachine.Request();  // Czekanie na wybór kawy
                coffeeMachine.Request();  // Podgrzewanie wody
                coffeeMachine.Request();  // Mielenie ziaren
                coffeeMachine.Request();  // Przygotowywanie kawy
                coffeeMachine.Request();  // Kawa gotowa, powrót do stanu wyłączonego
            }
        }
    }
}
