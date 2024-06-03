using StrategyPattern.Context;
using StrategyPattern.DataAccessStrategies;
using StrategyPattern.Strategy;

namespace StrategyPattern
{
    public class Program
    {
        public static void Main(string[] args)
        {
            IDataStrategy databaseStrategy = new DatabaseStrategy();
            DataAccessHandler databaseHandler = new DataAccessHandler(databaseStrategy);
            databaseHandler.Execute();

            IDataStrategy xmlStrategy = new XmlStrategy();
            DataAccessHandler xmlHandler = new DataAccessHandler(xmlStrategy);
            xmlHandler.Execute();
        }
    }
}