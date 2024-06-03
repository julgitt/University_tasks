using StatePattern.Context;

namespace StatePattern.State
{
    public interface IState
    {
        void Handle(CoffeeMachine context);
    }
}
