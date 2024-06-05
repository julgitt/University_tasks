using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata.Ecma335;
using System.Text;
using System.Threading.Tasks;

namespace zad1
{
    public class TimeSingleton
    {
        private static TimeSingleton? _instance;
        private static DateTime _timer = DateTime.Now;
        private static readonly object _lock = new();

        private static bool IsNewInstanceAllowed()
        {
            if (_instance == null)
                return true;
            TimeSpan time = DateTime.Now - _timer;
            return time.Seconds >= 5;
        }

        public static TimeSingleton Instance()
        {
            if (IsNewInstanceAllowed())
            {
                lock (_lock)
                {
                    if (IsNewInstanceAllowed())
                    {
                        _timer = DateTime.Now;
                        _instance = new TimeSingleton();
                    }
                }
            }
            return _instance;
        }

    }
}
