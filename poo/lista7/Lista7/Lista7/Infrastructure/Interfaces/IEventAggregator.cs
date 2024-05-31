namespace Lista7.Infrastructure.Interfaces
{
    public interface IEventAggregator
    {
        public void AddSubscriber<T>(ISubscriber<T> Subscriber);
        public void RemoveSubscriber<T>(ISubscriber<T> Subscriber);
        public void Publish<T>(T Event);
    }
}
