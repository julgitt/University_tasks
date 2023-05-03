using System;
using System.Collections;
using System.Collections.Generic;
using System.Dynamic;
using System.Linq.Expressions;
using System.Reflection;

namespace Task2List5
{
    class DynamicPerson : DynamicObject
    {
        private Dictionary<string, object> properties = new Dictionary<string, object>();

        public override bool TryGetMember(GetMemberBinder binder, out object result)
        {
            string name = binder.Name.ToLower();
            return properties.TryGetValue(name, out result);
        }

        public override bool TrySetMember(SetMemberBinder binder, object value)
        {
            string name = binder.Name.ToLower();
            properties[name] = value;
            return true;
        }

        public override bool TryGetIndex(GetIndexBinder binder, object[] indexes, out object result)
        {
            int index = (int)indexes[0];
            string key = $"item{index}";
            return properties.TryGetValue(key, out result);
        }

        public override bool TrySetIndex(SetIndexBinder binder, object[] indexes, object value)
        {
            int index = (int)indexes[0];
            string key = $"item{index}";
            properties[key] = value;
            return true;
        }

        // calling a method
        public override bool TryInvokeMember(InvokeMemberBinder binder, object[] args, out object result)
        {
            Type dictType = typeof(Dictionary<string, object>);
            try
            {
                result = dictType.InvokeMember(
                             binder.Name,
                             BindingFlags.InvokeMethod,
                             null, properties, args);
                return true;
            }
            catch
            {
                result = null;
                return false;
            }
        }

        public override bool TryInvoke(InvokeBinder binder, object[] args, out object result)
        {
            if ((args.Length == 3) &&
            (args[0].GetType() == typeof(String)) &&
            (args[1].GetType() == typeof(String)) &&
            (args[2].GetType() == typeof(int)))
            {
                properties["firstname"] = args[0];
                properties["lastname"] = args[1];
                properties["age"] = args[2];
                result = true;
                return true;
            }

            else
            {
                // If the number of arguments is wrong,
                // or if arguments are of the wrong type,
                // the method returns false.
                result = false;
                return false;
            }
        }

        public override bool TryUnaryOperation(UnaryOperationBinder binder, out object result)
        {
            String resultFirstName = "Mr. " + (String)properties["firstname"];
            String resultLastName = (String)properties["lastname"];
            int resultAge;
            // Checking what type of operation is being performed.
            switch (binder.Operation)
            {
                // (a++ ).
                case ExpressionType.Increment:
                    resultAge =
                        (int)properties["age"] + 1;
                    break;

                // (a-- ).
                case ExpressionType.Decrement:
                    resultAge =
                        (int)properties["age"] - 1;
                    break;
                default:
                    Console.WriteLine(
                        binder.Operation +
                        ": This unary operation is not implemented");
                    result = null;
                    return false;
            }

            dynamic finalResult = new DynamicPerson();
            finalResult.FirstName = resultFirstName;
            finalResult.LastName = resultLastName;
            finalResult.Age = resultAge;
            result = finalResult;
            return true;
        }

        public override bool TryBinaryOperation(BinaryOperationBinder binder, object arg, out object result)
        {
            String resultFirstName = (String)properties["firstname"];
            String resultLastName = (String)((DynamicPerson)arg).properties["lastname"];
            int resultAge;

            // Checking what type of operation is being performed.
            switch (binder.Operation)
            {
                // (a + b).
                case ExpressionType.Add:
                    resultAge =
                        (int)properties["age"] +
                        (int)((DynamicPerson)arg).properties["age"];
                    break;

                // (a - b).
                case ExpressionType.Subtract:
                    resultAge =
                        (int)properties["age"] -
                        (int)((DynamicPerson)arg).properties["age"];
                    break;
                default:
                    Console.WriteLine(
                        binder.Operation +
                        ": This binary operation is not implemented");
                    result = null;
                    return false;
            }

            dynamic finalResult = new DynamicPerson();
            finalResult.FirstName = resultFirstName;
            finalResult.LastName = resultLastName;
            finalResult.Age = resultAge;
            result = finalResult;
            return true;
        }
        public void Print()
        {
            foreach (var pair in properties)
                Console.WriteLine(pair.Key + " " + pair.Value);
            if (properties.Count == 0)
                Console.WriteLine("No elements in the properties.");
        }
    }
    class Program
    {
        public static void Main(string[] args)
        {
            // Creating a dynamic Person
            dynamic person = new DynamicPerson();

            //_______________ TrySetMember, TryGetMember___________________

            // Adding new dynamic properties.
            // TrySetMember called.
            person.FirstName = "Adam";
            person.LastName = "Kowalski";
            person.Age = 30;

            // Getting values of the dynamic properties.
            // TryGetMember called.
            Console.WriteLine("TrySetMember and TryGetMember: " + person.firstname + " " + person.lastname + " " + person.Age);

            // runtime exception
            // Console.WriteLine(person.address);


            //______________TryGetIndex,TrySetIndex_____________________________

            // TrySetMember called
            person.item0 = 0;
            // Get the property value by index
            // TryGetIndex called
            Console.WriteLine("\nperson[0]: " + person[0]);

            // Setting the property value by index.
            // TrySetIndex called.
            // also creates item1
            person[1] = 1;
            
            // Getting the Property1 value.
            // TryGetMember called.
            Console.WriteLine("person.item1: " + person.item1);

            // run-time exception
            // Console.WriteLine(person[3])

            //_____________TryInvoke, TryInvokeMember____________________________

            // TryInvoke called
            person("Marek", "Stasiński", 50);
            //person("Jan", "Nowak", "30");
            Console.WriteLine("\nAfter TryInvoke: " + person.firstname + " " + person.lastname + " " + person.Age);

            Console.WriteLine("\nperson.Print() before Clear(): ");
            person.Print();
            Console.WriteLine("\nCalling person.clear()");
            person.Clear();
            Console.WriteLine("\nperson.Print() after Clear(): ");
            person.Print();

            //______TryUnaryOperation,TryBinaryOperation_______________

            person.Age = 20;
            person.FirstName = "Aleksander";
            person.LastName = "Nowacki";

            dynamic person2 = new DynamicPerson();

            person2.Age = 21;
            person2.FirstName = "Jacek";
            person2.LastName = "Felicki";

            dynamic person3 = person + person2;
            dynamic person4 = person2 - person;
            dynamic person5 = ++person;
            Console.WriteLine("\nperson + person2: " + person3.firstname + " " + person3.lastname + " " + person3.Age);
            Console.WriteLine("person - person2: " + person4.firstname + " " + person4.lastname + " " + person4.Age);
            Console.WriteLine("++person: " + person5.firstname + " " + person5.lastname + " " + person5.Age);

        }
    }
}