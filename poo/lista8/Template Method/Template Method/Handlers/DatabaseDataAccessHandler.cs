using System.Data;
using System.Data.SqlClient;

namespace Template_Method.Handlers
{
    internal class DatabaseDataAccessHandler : DataAccessHandler
    {
        private SqlConnection connection;
        private string column = "Column";

        protected override void Connect()
        {
            connection = new SqlConnection("connection");
            connection.Open();
            Console.WriteLine("Connected to database.");
        }

        protected override object GetData()
        {
            string query = $"SELECT {column} FROM Table";
            SqlCommand command = new SqlCommand(query, connection);
            SqlDataAdapter adapter = new SqlDataAdapter(command);
            DataTable dataTable = new DataTable();
            adapter.Fill(dataTable);
            Console.WriteLine("Data retrieved from database.");
            return dataTable;
        }

        protected override void ProcessData(object data)
        {
            DataTable dataTable = (DataTable)data;
            decimal sum = 0;
            foreach (DataRow row in dataTable.Rows)
            {
                sum += Convert.ToDecimal(row[column]);
            }
            Console.WriteLine($"Sum of column values: {sum}");
        }

        protected override void Close()
        {
            connection.Close();
            Console.WriteLine("Database connection closed.");
        }
    }
}
