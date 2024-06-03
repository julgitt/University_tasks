using System.Data;
using System.Data.SqlClient;

using StrategyPattern.Strategy;

namespace StrategyPattern.DataAccessStrategies
{
    public class DatabaseStrategy : IDataStrategy
    {
        private SqlConnection connection;
        private string column = "column";

        public void Connect()
        {
            connection = new SqlConnection("connection");
            connection.Open();
            Console.WriteLine("Connected to database.");
        }

        public object GetData()
        {
            string query = $"SELECT {column} FROM Table";
            SqlCommand command = new SqlCommand(query, connection);
            SqlDataAdapter adapter = new SqlDataAdapter(command);
            DataTable dataTable = new DataTable();
            adapter.Fill(dataTable);
            Console.WriteLine("Data retrieved from database.");
            return dataTable;
        }

        public void ProcessData(object data)
        {
            DataTable dataTable = (DataTable)data;
            decimal sum = 0;
            foreach (DataRow row in dataTable.Rows)
            {
                sum += Convert.ToDecimal(row[column]);
            }
            Console.WriteLine($"Sum of column values: {sum}");
        }

        public void Close()
        {
            connection.Close();
            Console.WriteLine("Database connection closed.");
        }
    }
}
