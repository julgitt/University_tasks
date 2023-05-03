using System;

namespace Task6List4
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Linq;
    using System.Reflection;

    class Program
    {
        static void Main(string[] args)
        {
            string logFilePath = "log.txt";

            string[] lines = File.ReadAllLines(logFilePath);

            var logs = lines
                .Select(line => line.Split(' '))
                .Select(parts => new
                {
                    Time = parts[0],
                    IPAddress = parts[1],
                    RequestMethod = parts[2],
                    Resource = parts[3],
                    Status = parts[4]
                });



            var topThreeIPs = logs
                .GroupBy(log => log.IPAddress)
                .Select(group => new { IPAddress = group.Key, RequestCount = group.Count() })
                .OrderByDescending(x => x.RequestCount)
                .Take(3);

            foreach (var item in topThreeIPs)
            {
                Console.WriteLine($"{item.IPAddress} {item.RequestCount}");
            }
        }
    }
}