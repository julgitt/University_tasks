using StatePattern.State;
using StatePattern.Context;

namespace StatePattern.CoffeeMachineStates
{
    public class EndState : IState
    {
        public void Handle(CoffeeMachine context)
        {
            Console.WriteLine("Wyłączanie ekspresu...");
            context.SetState(new StartState());
        }
    }
}
