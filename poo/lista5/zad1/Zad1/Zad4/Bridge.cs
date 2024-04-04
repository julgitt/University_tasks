
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace Zad4
{
    public abstract class PersonNotifier
    {
        public abstract void Notify(IEnumerable<Person> parameters);
    }

    public abstract class PersonRegistry
    {
        protected PersonNotifier notifier;
        public PersonRegistry(PersonNotifier notifier)
        {
            this.notifier = notifier;
        }

        public abstract IEnumerable<Person> GetPersons();  

        public void Notify()
        {
            notifier.Notify(this.GetPersons());
        }
    }

    public class XMLPersonRegistry : PersonRegistry
    {
        public XMLPersonRegistry(PersonNotifier notifier) : base(notifier) { }

        public override IEnumerable<Person> GetPersons()
        {
            throw new NotImplementedException();
        }
    }

    public class SmtpPersonNotifier : PersonNotifier
    {
        public override void Notify(IEnumerable<Person> parameters)
        {
            foreach (var elem in parameters)
            {
                Console.WriteLine("Powadomiono" + elem.name);
            }
        }
    }

    public class Person
    {
        public string name;

        public Person(string name)
        {
            this.name = name;
        }
    }

    public class Program
    {
        static void Main(string[] args)
        {
            Person fstPerson = new Person("Kasia");
            Person sndPerson = new Person("Stasia");
            Person trdPerson = new Person("Jan");

            SmtpPersonNotifier notifier = new SmtpPersonNotifier();

            XMLPersonRegistry registry = new XMLPersonRegistry(notifier);

            var persons = registry.GetPersons();

            registry.Notify();

        }
    }


}
