namespace Template_Method.Handlers
{
    public abstract class DataAccessHandler
    {
        public void Execute()
        {
            Connect();
            var data = GetData();
            ProcessData(data);
            Close();
        }

        protected abstract void Connect();
        protected abstract object GetData();
        protected abstract void ProcessData(object data);
        protected abstract void Close();
    }
}