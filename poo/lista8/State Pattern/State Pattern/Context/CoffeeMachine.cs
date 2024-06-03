using StatePattern.State;
using StatePattern.CoffeeMachineStates;

namespace StatePattern.Context
{
    public class CoffeeMachine
    {
        private int coffee;
        private int water;

        public IState State { get; private set; }

        public CoffeeMachine()
        {
            State = new StartState();
            coffee = 10;
            water = 10;
        }


        public bool IsCoffeeOk()
        {
            return coffee > 0;
        }

        public bool IsWaterOk()
        {
            return water > 0;
        }

        public void UseWater()
        {
            water--;
        } 

        public void UseCoffee()
        {
            coffee--;
        }

        public void RefillCoffee()
        {
            coffee = 10;
        }

        public void RefillWater()
        {
            water = 10;
        }

        public void SetState(IState state)
        {
            State = state;
        }

        public void Request()
        {
            State.Handle(this);
        }
    }
}
