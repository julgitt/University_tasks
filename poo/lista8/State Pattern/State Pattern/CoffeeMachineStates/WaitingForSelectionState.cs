using StatePattern.State;
using StatePattern.Context;

namespace StatePattern.CoffeeMachineStates
{
    public class WaitingForSelectionState : IState
    {
        public void Handle(CoffeeMachine context)
        {
            Console.WriteLine("Czekanie na wybór kawy...");

            if (Console.ReadLine() == "Select")
            {
                context.SetState(new HeatingWaterState());
            }
            else
            {
                context.SetState(new EndState());
            }
        }
    }
}
