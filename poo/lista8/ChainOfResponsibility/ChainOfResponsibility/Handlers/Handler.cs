using ChainOfResponsibility.Requests;

namespace ChainOfResponsibility.Handlers
{
    public abstract class Handler
    {
        protected Handler? _nextHandler;

        public abstract bool ProcessRequest(Request request);

        public void DispatchRequest(Request request)
        {
            bool result = ProcessRequest(request);
            if (!result && _nextHandler != null)
                _nextHandler.DispatchRequest(request);
        }


        public void AttachHandler(Handler handler)
        {
            if (_nextHandler != null)
                _nextHandler.AttachHandler(handler);
            else
                _nextHandler = handler;
        }
    }

}
