using StatePattern.State;
using StatePattern.Context;

namespace StatePattern.CoffeeMachineStates
{
    public class GrindingBeansState : IState
    {
        public void Handle(CoffeeMachine context)
        {
            Console.WriteLine("Mielenie ziaren...");
            bool beansGround = true;

            if (beansGround)
            {
                context.SetState(new MakingCoffeeState());
            }
        }
    }
}
