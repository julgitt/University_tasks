/*  Napisać w C# dowolny program demonstrujący użycie klas (metod, pól, propercji, indekserów, delegacji i zdarzeń) oraz podstawowych konstrukcji składniowych (pętle, instrukcje warunkowe, switch) i zdekompilować go za pomocą narzędzia IlSpy (http://ilspy.net/).
Otrzymany kod skompilować (ilasm), aby otrzymać plik wynikowy. Plik ten następnie
zdekompilować na powrót do języka C#.
Porównać otrzymane w ten sposób pliki z kodem źródłowym. Jak objawiają się i z czego
wynikają różnice? */

using System;
using System.Collections.Generic;

namespace Task1_List1
{
    /// <summary>
    /// Solution
    /// </summary>

    public class Example
    {
        // field
        int []array;

        // constructors
        public Example() 
        { 
            array = new int[] {1}; 
        }
        // params - keyword for using multiple arguments (array of arguments)
        public Example(params int[] input)
        {
            array = new int[input.Length];
            for (int i = 0; i < input.Length; i++)
                array[i] = input[i];
        }

        // methods
        public void printArray()
        {
            for (int i = 0; i < array.Length; i++)
            {
                Console.WriteLine(array[i]);
            }

        }

        // indexer - so we can index object of this class
        public int this[int i]
        {
            get { return array[i]; }
            set { array[i] = value; }
        }

        // properties
        public int numberOfElements
        {
            get { return array.Length; }
        }
    }

    // delegat
    public delegate void PerformCalculation(int x, int y);
    public class Calculation
    {
        public void printAdd(int x, int y) { Console.WriteLine(x + y); }
        public void printSub(int x, int y) { Console.WriteLine(x - y); }
    }

    // events
    public delegate void Notify();  // delegate

    public class EventExample
    {
        public event Notify ProcessCompleted; // event

        public void StartProcess()
        {
            Console.WriteLine("Process Started!");
            OnProcessCompleted();
        }

        protected virtual void OnProcessCompleted() //protected virtual method
        {
            //if ProcessCompleted is not null then call delegate
            Console.WriteLine("Process Completed!");
            ProcessCompleted?.Invoke();
        }
    }


    class Program
    {
        static void Main()
        {
            Calculation calculation = new Calculation();
            PerformCalculation perform = new PerformCalculation(calculation.printAdd);

            Console.WriteLine("Calling the delegate:");
            perform(5, 5); // delegate

            Console.WriteLine("Event example:");
            EventExample new_event = new EventExample();
            new_event.StartProcess();

            Console.WriteLine("Example class with indexer:");
            Example example = new Example(1, 2, 3);
            Example example2 = new Example();
            example[0] = 4;
            example[1] = 5;

            for (int i = 0; i < example.numberOfElements; i++)
            {
                Console.WriteLine(example[i]);
            }

            Console.WriteLine("If with boolean variables:");
            bool t = true, f = false;

            if (t)
                Console.WriteLine(t);
            else
                Console.WriteLine(f);

            if (f)
                Console.WriteLine(t);
            else
                Console.WriteLine(f);

            Console.WriteLine("Switch case:");
            int caseSwitch = 5;

            switch (caseSwitch)
            {
                case 1: 
                    Console.WriteLine("Case 1"); 
                    break;
                case 2: 
                    Console.WriteLine("Case 2"); 
                    break;
                case 3: 
                    Console.WriteLine("Case 3"); 
                    break;
                default: 
                    Console.WriteLine("Case default"); 
                    break;
            }
            Console.ReadLine();
        }
    }

}
