namespace Lista7.Infrastructure.Interfaces
{
    public interface IEventAggregator
    {
        void AddSubscriber<T>(ISubscriber<T> Subscriber);
        void RemoveSubscriber<T>(ISubscriber<T> Subscriber);
        void Publish<T>(T Event);
    }
}
