using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata.Ecma335;
using System.Text;
using System.Threading.Tasks;

namespace zad1
{
    public class ThreadSingleton
    {
        private static readonly ThreadLocal<ThreadSingleton> _instance =  new ThreadLocal<ThreadSingleton>();

        public static ThreadSingleton Instance()
        {
            if (_instance.Value == null)
            {
                _instance.Value = new ThreadSingleton();
            }   

            return _instance.Value;
        }

    }
}
