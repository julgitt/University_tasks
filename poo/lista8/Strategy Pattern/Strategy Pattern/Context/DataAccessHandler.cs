using StrategyPattern.Strategy;

namespace StrategyPattern.Context
{
    public class DataAccessHandler
    {
        private readonly IDataStrategy _dataStrategy;

        public DataAccessHandler(IDataStrategy dataStrategy)
        {
            _dataStrategy = dataStrategy;
        }

        public void Execute()
        {
            _dataStrategy.Connect();
            var data = _dataStrategy.GetData();
            _dataStrategy.ProcessData(data);
            _dataStrategy.Close();
        }
    }
}
