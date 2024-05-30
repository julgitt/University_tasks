using Lista7.ViewModels.Interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lista7.ViewModels.Classes
{
    public class EventAggregator
    {
        private static readonly Dictionary<Type, List<object>> _subscribers = new Dictionary<Type, List<object>>();

        public static void AddSubscriber<T>(ISubscriber<T> subscriber)
        {
            if (!_subscribers.ContainsKey(typeof(T)))
                _subscribers[typeof(T)] = new List<object>();

            _subscribers[typeof(T)].Add(subscriber);
        }

        public static void RemoveSubscriber<T>(ISubscriber<T> subscriber)
        {
            if (_subscribers.ContainsKey(typeof(T)))
                _subscribers[typeof(T)].Remove(subscriber);
        }

        public static void Publish<T>(T notification)
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
