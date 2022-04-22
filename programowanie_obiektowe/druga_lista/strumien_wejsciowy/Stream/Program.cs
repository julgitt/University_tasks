using System;

namespace Stream
{
    public class IntStream
    {
        protected int current_number;

        //constructor
        public IntStream()
        {
            current_number = -1;
        }

        //methods
        virtual public int Next()
        {
            if (Eos())
            {
                Console.WriteLine($"Current number is larger than maximum value");
                return -1;
            }
            current_number++;
            return current_number;
        }

        virtual public bool Eos()
        {
            if (current_number == Int32.MaxValue)
            {
                return true;
            }
            return false;
        }

        public void Reset()
        {
            current_number = -1;
        }
    }

    public class PrimeStream : IntStream
    {
      
        //check if next value is prime number
        private bool Is_prime(int number)
        {
            if (number < 2)
                return false;

            for (int i = 2; i * i <= number; i++)
                if (number % i == 0)
                    return false;
            return true;
        }


        //override Next() method
        override public int Next()
        {
            if (Eos())
            {
                Console.WriteLine($"Current number is larger than maximum value");
                return -1;
            }

            current_number++;

            while (!Is_prime(current_number))
            {
                if (Eos())
                {
                    Console.WriteLine($"Current number is larger than maximum value");
                    return -1;
                }
                current_number++;
            }

            return current_number;
        }
    }
    public class RandomStream : IntStream
    {
        //override methods
        override public int Next()
        {
            int randomInt = new Random().Next();
            return randomInt;
        }
        override public bool Eos()
        {
            return false;
        }
    }
    
    //String Stream Class
    public class RandomWordStream
    {
        private PrimeStream string_length;
        private RandomStream random_int;

        //constructor
        public RandomWordStream()
        {
            string_length = new PrimeStream();
            random_int = new RandomStream();
        }

        //next string
        public string Next()
        {
            int length = string_length.Next();
            string result = "";
            while (0 < length)
            {
                result += (char)((random_int.Next()) % 96 + 32);
                length--;
            }
            return result;
        }
    }

    //test
    public class Stream
    {
        public static void Main(string[] args)
        {
            //liczby naturalne
            IntStream naturalne = new IntStream();
            Console.WriteLine("Naturalne: \n" + naturalne.Next());
            Console.WriteLine(naturalne.Next());
            Console.WriteLine(naturalne.Next());
            Console.WriteLine(naturalne.Next());
            naturalne.Reset();
            Console.WriteLine(naturalne.Next());
            Console.WriteLine(naturalne.Next());
            Console.WriteLine("eos: " + naturalne.Eos());

            Console.WriteLine("\n");
            //liczby pierwsze
            IntStream pierwsze = new PrimeStream();
            Console.WriteLine("Pierwsze: \n" + pierwsze.Next());
            Console.WriteLine(pierwsze.Next());
            Console.WriteLine(pierwsze.Next());
            Console.WriteLine(pierwsze.Next());

            pierwsze.Reset();
            Console.WriteLine(pierwsze.Next());
            Console.WriteLine(pierwsze.Next());
            Console.WriteLine("eos: " + pierwsze.Eos());

            Console.WriteLine("\n");

            //losowe liczby
            IntStream random = new RandomStream();
            Console.WriteLine("Random: \n" + random.Next());
            Console.WriteLine(random.Next());
            Console.WriteLine(random.Next());
            Console.WriteLine(random.Next());

            random.Reset();
            Console.WriteLine(random.Next());
            Console.WriteLine(random.Next());
            Console.WriteLine("eos: " + random.Eos());

            Console.WriteLine("\n");

            //losowy string
            RandomWordStream rws = new RandomWordStream();
            Console.WriteLine("Random String: \n" + rws.Next());
            Console.WriteLine(rws.Next());

        }
    }  
}
