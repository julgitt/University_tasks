using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad3
{
    class Adapter
    {
        class ComparisonAdapter<T> : IComparer
        {
            private readonly Comparison<T> comparison;

            public ComparisonAdapter(Comparison<T> comparison)
            {
                this.comparison = comparison;
            }

            public int Compare(object x, object y)
            {
                if (x == null && y == null)
                    return 0;
                if (x == null)
                    return -1;
                if (y == null)
                    return 1;

                if (x is T && y is T)
                {
                    return comparison((T)x, (T)y);
                }

                throw new ArgumentException("Objects must be of type T");
            }
        }

        static int IntComparer(int x, int y)
        {
            return x.CompareTo(y);
        }

        static void Main(string[] args)
        {
            ArrayList a = new ArrayList() { 1, 5, 3, 3, 2, 4, 3 };
            a.Sort(new ComparisonAdapter<int>(IntComparer));

            for (int i = 0; i < a.Count; i++) 
            {
                Console.WriteLine(a[i]);
            }
            Console.ReadLine();
        }
    }
}
