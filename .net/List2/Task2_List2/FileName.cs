using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task2_List2
{
    // nadaje 'ksztalt obiektów dziedziczących z tej klasy, dzieki metodom abstrakcyjnym
    // troche podobne do interfejsu, ale jednak jest to klasa 
    // nie można tworzyć instancji bezpośrednio tej klasy!
    // nie moze byc private pol
    // jezeli w klasie jest abstrakcyjna metoda to klasa tez musi byc abstract
    public abstract class Animal
    {
        // musimy nadpisac
        public abstract void sound();
        public void sleep()
        {
            Console.WriteLine("Zzzz");
        }
    }

    class Dog : Animal
    {
        // mozemy dalej nadpisac, ale gdy dodamy sealed, to nie bedziemy mogli
        public override void sound()
        {
            Console.WriteLine("woof");
        }
    }
    class Puppy : Dog
    {
        //mozna ale nie trzeba override'ować
        public override void sound()
        {
            Console.WriteLine("hau");
        }
    }

    // nie mozna dziedziczyc
    // moze byc rozsiane po kilku plikach zrodlowych
    // przydatne np. gdy kilka osob pracuje nad jedna duza klasa
    public partial class Employee
    {
        public void DoWork()
        {
            Console.WriteLine("Working..");
        }
    }

    public partial class Employee
    {
        public void GoToLunch()
        {
            Console.WriteLine("Eating..");
        }
    }

    // nie tworzymy obiektów z tej klasy, nie możemy też jej dziedziczyć. Jest tak jaby jedna instancja tej klasy
    // z kolei statyczne pola oznaczaja ze pole to jest jedno dla kazdej instancji obiektu
    // static class tez jest sealed, co wiecej nie moze dziedziczyc z innych klas
    static class Person
    {

        // pola musza byc statyczne
        public static string Name = "Jan";
        public static string Address = "Wroclaw";


        // metody też
        public static void details()
        {
            Console.WriteLine("The details of Person is:");
        }
    }
    // nie moze byc dziedziczona
    // nie ma access modifiers
    // sealed na metodach, polach - po odziedziczeniu nie mozemy zmienic definicji
    sealed class SealedClass
    {
        // nie mozemy modyfikowac tej wartosci
        public readonly string name = "Jan";
        // static jest ustawiony przed konstruktorem
        public static string surname = "Kowalski";
        // in nie moze byc zmodyfikowane, ref moze byc, out musi byc
        public int Add(in int x, ref int y, out int z)
        {
            // to musimy zrobic
            z = x + y;
            // to mozemy zrobic
            y++;

            //x++; tego nie mozemy zrobic
            return x + y;
        }
    }
    class VirtualMethod_Base_Class
    {
        // nie mozemy nadpisac
        public void show()
        {
            Console.WriteLine("Hello from base class!");
        }
        // mozemy nadpisac
        public virtual void virtual_show()
        {
            Console.WriteLine("Virtual Hello from base class!");
        }
    }

    // Derived Class  
    class Override_Method_Derived_Class : VirtualMethod_Base_Class
    {
        // mozemy nadpisac
        public override void virtual_show()
        {
            Console.WriteLine(" Overrided Hello form derived class!");
        }
    }


    class Program
    {
        static void Main(string[] args)
        {
            // do abstrakcyjnej
            //var animal = new Animal() nie mozemy 
            Console.WriteLine("Abstract class testing:");
            var dog = new  Dog();
            var puppy = new Puppy();

            dog.sound();
            puppy.sound();

            // do partial
            Console.WriteLine("Partial class testing:");
            var employee = new Employee();
            employee.DoWork();
            employee.GoToLunch();

            // wywolanie statycznej metody klasy Person
            Console.WriteLine("Static class testing:");
            Person.details();

            // Dostep do statycznych pol klasy Person
            Console.WriteLine("Person Name: " + Person.Name);
            Console.WriteLine("Person Address: " + Person.Address);


            // sealed
            Console.WriteLine("Static class member: " + SealedClass.surname);
            Console.WriteLine("Sealed class testing:");
            SealedClass myObject = new SealedClass();

            //Console.WriteLine("Static class member: " +  myObject.surname); nie mozemy tak zrobic

            int _in = 2, _ref = 5, _out; // out moze byc niezainicjalizowana w chwili wywolania funckcji w ktorej jest argumentem
            Console.WriteLine("name: " + myObject.name);
            Console.WriteLine("sum of two number: " + myObject.Add(_in, ref _ref, out _out));

            //virtual
            Console.WriteLine("Virtual/Override methods testing:");
            VirtualMethod_Base_Class virt = new VirtualMethod_Base_Class();
            virt.virtual_show();

            Override_Method_Derived_Class over = new Override_Method_Derived_Class();
            over.virtual_show();
        }
    }
}

