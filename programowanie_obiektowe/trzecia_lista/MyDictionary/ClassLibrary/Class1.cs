using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassLibrary
{
    public class MyDictionary<K, V>
    {
        private MyDictionary<K, V> next;
        private Tuple<K, V> element;

        public void Insert(K key, V element)
        {
            if (object.Equals(this.element, null))
            {
                this.element = Tuple.Create(key, element);
            }
            else
            {
                if (object.Equals(this.element.Item1, key))
                {
                    throw new ArgumentException();
                }
                if (this.next != null)
                {
                    this.next.Insert(key, element);
                }
                this.next = new MyDictionary<K, V>();
                this.next.element = Tuple.Create(key, element);
            }
        }

        public V Find_element(K key)
        {
            if (this.element == null)
            {
                throw new ArgumentException();
            }
            if (object.Equals(this.element.Item1, key))
            {
                return this.element.Item2;
            }
            if (this.next != null)
            {
                return this.next.Find_element(key);
            }
            throw new ArgumentException("there is no element with this key");
        }

        public void Del(K key)
        {
            if (object.Equals(this.element.Item1, key))
            {
                this.element = null;
            }
            else if (this.next != null)
            {
                if (object.Equals(this.next.element.Item1, key))
                {
                    this.next = this.next.next;
                }
                else
                    this.next.Del(key);
            }
            else if (this.next == null)
                throw new ArgumentException("there is no element with this key");
        }
    }
}
