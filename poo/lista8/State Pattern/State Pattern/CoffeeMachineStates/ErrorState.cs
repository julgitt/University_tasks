using System.Threading;

using StatePattern.State;
using StatePattern.Context;

namespace StatePattern.CoffeeMachineStates
{
    public class ErrorState : IState
    {
        public void Handle(CoffeeMachine context)
        {
            Console.WriteLine("Wykryto błąd! Brak wody lub kawy.");
            Thread.Sleep(1000);
            if (Console.ReadLine() == "Refill")
            {
                context.SetState(new RefillingState());
            }
            else
            {
                context.SetState(new EndState());
            }
        }
    }
}
