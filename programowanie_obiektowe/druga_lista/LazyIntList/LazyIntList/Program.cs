using System;
using System.Collections.Generic;

namespace LazyIntList
{
    public class LazyIntList
    {
        protected List<int> list;

        public LazyIntList()
        {
            list = new List<int>();
        }

        virtual public int Element(int i)
        {
            if (i <= 0)
                return -1;
               
            while (Size() < i)
            {
                list.Add(Size());
            }

            return list[i - 1];
        }
        public int Size()
        {
            return list.Count;
        }
    }

    public class LazyPrimeList : LazyIntList
    {
        private bool Is_prime(int number)
        {
            if (number < 2)
                return false;

            for (int i = 2; i * i <= number; i++)
                if (number % i == 0)
                    return false;
            return true;
        }

        public override int Element(int i)
        {
            int current_value;

            if (i <= 0)
                return -1;
            
            if (Size() == 0)
                current_value = 1;
            else
                current_value = list[Size()-1] + 1;

            while (Size() < i)
            {
                while (!Is_prime(current_value))
                {
                    current_value++;
                }
                list.Add(current_value);
                current_value = list[Size() - 1] + 1;
            }
            
            return list[i-1];
        }
    }

    //test
    class Program
    {
        static void Main(string[] args)
        {
            LazyIntList list = new LazyIntList();
            Console.WriteLine(list.Element(40));
            Console.WriteLine(list.Element(40));
            Console.WriteLine(list.Size());
            Console.WriteLine(list.Element(39));
            Console.WriteLine(list.Size());

            LazyPrimeList list2 = new LazyPrimeList();
            Console.WriteLine(list2.Element(0));
            Console.WriteLine(list2.Element(1));
            Console.WriteLine(list2.Size());
            Console.WriteLine(list2.Element(7));
            Console.WriteLine(list2.Size());
            Console.WriteLine(list2.Element(5));
            Console.WriteLine(list2.Size());
        }
    }
}
