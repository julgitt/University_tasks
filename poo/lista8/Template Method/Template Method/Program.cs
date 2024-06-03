using Template_Method.Handlers;

namespace Template_Method
{
    public class Program
    {
        public static void Main(string[] args)
        {
            DataAccessHandler databaseHandler = new DatabaseDataAccessHandler();
            databaseHandler.Execute();

            DataAccessHandler xmlHandler = new XmlDataAccessHandler();
            xmlHandler.Execute();
        }
    }
}