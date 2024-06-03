namespace StrategyPattern.Strategy
{
    public interface IDataStrategy
    {
        void Connect();
        object GetData();
        void ProcessData(object data);
        void Close();
    }
}
