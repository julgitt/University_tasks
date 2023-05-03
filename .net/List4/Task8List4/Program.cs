using System;

namespace Task8List4
{
    class Program
    {
        public static Func<A, R> Y<A, R>(Func<Func<A, R>, Func<A, R>> f)
        {
            Func<A, R> g = null;
            g = f(a => g(a));
            return g;
        }
        public static void Main(string[] args)
        {
            List<int> list = new List<int>() { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };


            foreach (var item in list.Select(i =>
                Y<int, int>(f =>
                    delegate (int n)
                    {
                        if (n <= 2)
                            return 1;
                        else
                            return f(n - 1) + f(n - 2);
                    })(i)))
            {
                Console.WriteLine(item);
            }
        }

    }
}