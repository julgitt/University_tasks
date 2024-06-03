using StatePattern.State;
using StatePattern.Context;

namespace StatePattern.CoffeeMachineStates
{
    public class StartState : IState
    {
        public void Handle(CoffeeMachine context)
        {
            Console.WriteLine("Włączanie ekspresu...");
            context.SetState(new CheckState());
        }
    }
}
