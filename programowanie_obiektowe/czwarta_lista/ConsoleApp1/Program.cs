using System;
using System.Collections;


namespace ConsoleApp1
{
    class Program
    {
        public class PrimeCollection : IEnumerable
        {
            public IEnumerator GetEnumerator()
            {
                return new ListEnum();
            }

            public class ListEnum : IEnumerator
            {
                private int prime_number;

                public bool Is_prime(int number)
                {
                    if (number < 2)
                        return false;

                    for (int i = 2; i * i <= number; i++)
                        if (number % i == 0)
                            return false;
                    return true;
                }

                public ListEnum()
                {
                    prime_number = 2;
                }

                public bool MoveNext()
                {
                    while (prime_number != int.MaxValue)
                    {
                        if (Is_prime(prime_number))
                        {
                            return true;
                        }
                        prime_number++;
                    }
                    return false;
                }
                public object Current
                {
                    get
                    {
                        return prime_number++;
                    }
                }
                public void Reset()
                {
                    prime_number = 2;
                }
            }
        }
        static void Main(string[] args)
        {
            PrimeCollection pc = new PrimeCollection();
            foreach (int p in pc)
            {
                if (99 < p)
                    break;
                Console.WriteLine(p);
            }

        }
    }
}

