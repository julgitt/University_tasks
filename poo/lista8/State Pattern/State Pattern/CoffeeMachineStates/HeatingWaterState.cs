using StatePattern.State;
using StatePattern.Context;

namespace StatePattern.CoffeeMachineStates
{
    public class HeatingWaterState : IState
    {
        public void Handle(CoffeeMachine context)
        {
            Console.WriteLine("Podgrzewanie wody...");
            bool waterHeated = true;
            
            context.UseWater();

            if (waterHeated)
            {
                context.SetState(new GrindingBeansState());
            }
        }
    }
}
