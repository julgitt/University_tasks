using System;

namespace Task1_List2_1
{
    public class SameAssemblyBaseClass
    {
        public string public_var = "public";
        protected string protected_var = "protected";
        protected internal string protected_Internal_var = "protected internal";
        internal string internal_var = "internal";
        private string private_var = "private";
        public void Test_1()
        {
            // OK
            Console.WriteLine(private_var);

            // OK
            Console.WriteLine(public_var);

            // OK
            Console.WriteLine(protected_var);

            // OK
            Console.WriteLine(internal_var);

            // OK
            Console.WriteLine(protected_Internal_var);
        }
    }

    public class SameAssemblyDerivedClass : SameAssemblyBaseClass
    {
        public void Test_2()
        {
            SameAssemblyDerivedClass p = new SameAssemblyDerivedClass();

            // NOT OK
            // Console.WriteLine(private_var);

            // OK
            Console.WriteLine(p.public_var);

            // OK
            Console.WriteLine(p.protected_var);

            // OK
            Console.WriteLine(p.internal_var);

            // OK
            Console.WriteLine(p.protected_Internal_var);
        }
    }

    public class SameAssemblyDifferentClass
    {
        public SameAssemblyDifferentClass()
        {
            SameAssemblyBaseClass p = new SameAssemblyBaseClass();

            // OK
            Console.WriteLine(p.public_var);

            // OK
            Console.WriteLine(p.internal_var);

            // NOT OK
            // Console.WriteLine(private_var);

            // Error : 'Task1_List2.SameAssemblyBaseClass.protected_var' is inaccessible due to its protection level
            //Console.WriteLine(p.protected_var);

            // OK
            Console.WriteLine(p.protected_Internal_var);
        }
    }
}