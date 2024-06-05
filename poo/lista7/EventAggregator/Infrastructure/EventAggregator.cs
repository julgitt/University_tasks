using Lista7.Infrastructure.Interfaces;

namespace Lista7.Infrastructure
{
    public class EventAggregator : IEventAggregator
    {
        private readonly Dictionary<Type, List<object>> _subscribers = new Dictionary<Type, List<object>>();

        public void AddSubscriber<T>(ISubscriber<T> subscriber)
        {
            if (!_subscribers.ContainsKey(typeof(T)))
                _subscribers[typeof(T)] = new List<object>();

            _subscribers[typeof(T)].Add(subscriber);
        }

        public void RemoveSubscriber<T>(ISubscriber<T> subscriber)
        {
            if (_subscribers.ContainsKey(typeof(T)))
                _subscribers[typeof(T)].Remove(subscriber);
        }

        public void Publish<T>(T notification)
        {
            if (_subscribers.ContainsKey(typeof(T)))
            {
                foreach (var subscriber in _subscribers[typeof(T)].OfType<ISubscriber<T>>())
                {
                    subscriber.Handle(notification);
                }
            }
        }
    }

}
