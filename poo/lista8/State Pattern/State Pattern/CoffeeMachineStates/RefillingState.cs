using StatePattern.State;
using StatePattern.Context;

namespace StatePattern.CoffeeMachineStates
{
    public class RefillingState : IState
    {
        public void Handle(CoffeeMachine context)
        {
            Console.WriteLine("Uzupełnianie wody i kawy...");
            context.RefillCoffee();
            context.RefillWater();
            bool refilled = context.IsCoffeeOk() && context.IsWaterOk();

            if (refilled)
            {
                Console.WriteLine("Uzupełniono wodę i kawę.");
                context.SetState(new CheckState());
            }
            else
            {
                context.SetState(new EndState());
            }
        }
    }
}
