using StatePattern.State;
using StatePattern.Context;

namespace StatePattern.CoffeeMachineStates
{
    public class MakingCoffeeState : IState
    {
        public void Handle(CoffeeMachine context)
        {
            Console.WriteLine("Przygotowywanie kawy...");
            bool coffeeMade = true;

            context.UseCoffee();

            if (coffeeMade)
            {
                Console.WriteLine("Kawa gotowa");
                context.SetState(new EndState());
            }
        }
    }
}
