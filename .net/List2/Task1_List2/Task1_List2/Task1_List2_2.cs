using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using Task1_List2_1;

namespace Task1_List2
{
    class DifferentAssemblyClass
    {
        public DifferentAssemblyClass()
        {
            SameAssemblyBaseClass p = new SameAssemblyBaseClass();

            // NOT OK
            // Console.WriteLine(p.private_var);

            // NOT OK
            // Console.WriteLine(p.internal_var);

            // OK
            Console.WriteLine(p.public_var);

            // Error : 'Task1_list2.SameAssemblyBaseClass.protected_var' is inaccessible due to its protection level
            // Console.WriteLine(p.protected_var);

            // Error : 'Task1_List2.SameAssemblyBaseClass.protected_Internal_var' is inaccessible due to its protection level
            // Console.WriteLine(p.protected_Internal_var);
        }
    }

    class DifferentAssemblyDerivedClass : SameAssemblyBaseClass
    {
        static void Main(string[] args)
        {
            DifferentAssemblyDerivedClass p = new DifferentAssemblyDerivedClass();

            // NOT OK
            // Console.WriteLine(p.private_var);

            // NOT OK
            //Console.WriteLine(p.internal_var);

            // OK
            Console.WriteLine(p.public_var);

            // OK
            Console.WriteLine(p.protected_var);

            // OK
            Console.WriteLine(p.protected_Internal_var);

            SameAssemblyDerivedClass dd = new SameAssemblyDerivedClass();
            dd.Test_1();
        }
    }
}
}