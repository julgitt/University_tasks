using System;
using System.Collections;

namespace ListCollection
{
    class Program
    {
        public interface IListCollection<T>
        {
            public T Pop();
            public void Push(T element);
            public bool IsEmpty();
        }

        public class Node<T>
        {
            public Node<T> prev;
            public Node<T> next;
            public T element;

            //constructors
            public Node()
            {
                element = default;
            }
            public Node(T element)
            {
                this.element = element;
            }

            public T ReturnElementByIndex(int index)
            {
                if (index == 0)
                    return element;
                if (next == null)
                    throw new ArgumentException("There is no element with given index");
                return next.ReturnElementByIndex(index - 1);
            }
        }
        public class List<T> : IEnumerable, IListCollection<T>
        {

            Node<T> head;
            Node<T> tail;

            //constructor
            public List()
            {
                head = null;
                tail = null;
            }

            public IEnumerator GetEnumerator()
            {
                if (head == null)
                    throw new ArgumentException("list is empty");
                return new ListEnum<T>(head);
            }
            public T this[int index]
            {
                get
                {
                    if (head == null)
                        throw new ArgumentException("list is empty");
                    return head.ReturnElementByIndex(index);
                }
            }
            public int Length
            {
                get
                {
                    Node<T> temp = head;
                    int length = 0;
                    while (temp != null)
                    {
                        temp = temp.next;
                        length++;
                    }
                    return length;
                }
            }
            public override string ToString()
            {
                return String.Format("List with {0} elements", Length);
            }
            public void Push_back(T elem)
            {
                Node<T> temp = new Node<T>(elem);
                if (IsEmpty())
                {
                    head = temp;
                    tail = head;
                    return;
                }
                else
                {
                    temp.prev = tail;
                    tail.next = temp;
                    tail = temp;
                }
            }
            public void Push_front(T elem)
            {
                Node<T> temp = new Node<T>(elem);
                if (IsEmpty())
                {
                    head = temp;
                    tail = head;
                }
                else
                {
                    temp.next = head;
                    head.prev = temp;
                    head = temp;
                }
            }
            public T Pop_back()
            {
                if (tail == null)
                {
                    throw new Exception("list is empty");
                }
                T temp = tail.element;
                tail = tail.prev;
                if (tail != null)
                    tail.next = null;
                else
                    head = null;
                return temp;
            }
            public T Pop_front()
            {
                if (head == null)
                {
                    throw new ArgumentException("Invalid argument!");
                }
                T temp = head.element;
                head = head.next;
                if (head != null)
                    head.prev = null;
                else
                    tail = null;
                return temp;
            }
            public T Pop()
            {
                return Pop_front();
            }
            public void Push(T elem)
            {
                Push_front(elem);
            }
            public bool IsEmpty()
            {
                if (head == null || tail == null)
                    return true;
                return false;
            }
        }

        public class Stack<T> : IListCollection<T>
        {
            T element;
            Stack<T> next;
            bool empty;

            public Stack()
            {
                element = default;
                empty = false;
            }
            public Stack(T elem)
            {
                element = elem;
                empty = false;
            }

            public void Push(T element)
            {
                Stack<T> temp = this;
                while (temp.next != null)
                {
                    temp = temp.next;
                }

                temp.next = new Stack<T>(element);
                empty = false;
            }

            public T Pop()
            {
                Stack<T> temp = this;
                Stack<T> previous = temp;
                
                if (IsEmpty())
                {
                    throw new Exception("there is nothing to delete");
                }
                if (this.next == null)
                {
                    empty = true;
                    return this.element;
                }
                while (temp.next != null)
                {
                    previous = temp;
                    temp = temp.next;
                }
                T deleted = temp.element;
                previous.next = null;
                return deleted;
            }
            public bool IsEmpty()
            {
                if (element == null && next == null)
                    return true;
                if (empty) return true;
                return false;
            }
        }

        class ListEnum<T> : IEnumerator
        {

            Node<T> current;
            Node<T> list;
            public ListEnum(Node<T> lst)
            {
                list = lst;
            }
            public bool MoveNext()
            {
                if (this.current == null) 
                    this.current = this.list;
                else 
                    this.current = this.current.next;
                return this.current != null;

            }
            public object Current
            {
                get
                {
                    if (current != null)
                        return current.element;
                    else
                        return list.element;
                }
            }
            public void Reset()
            {
                current = list;
            }
        }
        static void Main(string[] args)
        {
            List<int> list1 = new List<int>();

            Console.WriteLine("Check if list is empty: " + list1.IsEmpty());
            list1.Push(1);
            list1.Push(2);
            list1.Push(3);
            Console.WriteLine("Check if list is empty: " + list1.IsEmpty());
            Console.WriteLine("length: " + list1.Length);
            Console.WriteLine("toString(): " + list1.ToString());
            Console.WriteLine("First element: " + list1[0]);
            Console.WriteLine("Second element: " + list1[1]);
            Console.WriteLine("Third element: " + list1[2]);
            //Console.WriteLine("Fourth element: " + list1[3]);
            Console.WriteLine("Foreach loop:");
            foreach (int x in list1)
            {
                Console.WriteLine(x);
            }

            Stack<int> list2 = new Stack<int>();

            Console.WriteLine("Check if list is empty: " + list2.IsEmpty());
            list2.Push(1);
            list2.Push(2);
            list2.Push(3);
            Console.WriteLine("Check if list is empty: " + list2.IsEmpty());

            Console.WriteLine("deleted: " + list2.Pop());
            Console.WriteLine("deleted: " + list2.Pop());
            Console.WriteLine("deleted: " + list2.Pop());
            Console.WriteLine("deleted: " + list2.Pop());
            Console.WriteLine("Check if list is empty: " + list2.IsEmpty());
     
        }
    }
}