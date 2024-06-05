using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata.Ecma335;
using System.Text;
using System.Threading.Tasks;

namespace zad1
{
    public class ProcessSingleton
    {
        private static ProcessSingleton? _instance;
        private static readonly object _lock = new();

        public static ProcessSingleton Instance() 
        {
            if (_instance == null)
            {
                lock (_lock)
                {
                    if (_instance == null)
                    {
                        _instance = new ProcessSingleton();
                    }
                }

            }

            return _instance;
        }

    }
}
