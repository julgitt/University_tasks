using StatePattern.State;
using StatePattern.Context;

namespace StatePattern.CoffeeMachineStates
{
    public class CheckState : IState
    {
        public void Handle(CoffeeMachine context)
        {
            Console.WriteLine("Sprawdzanie stanu...");
            bool waterOk = context.IsWaterOk();
            bool coffeeOk = context.IsCoffeeOk();

            if (!waterOk || !coffeeOk)
            {
                context.SetState(new ErrorState());
            }
            else
            {
                context.SetState(new WaitingForSelectionState());
            }
        }
    }
}
