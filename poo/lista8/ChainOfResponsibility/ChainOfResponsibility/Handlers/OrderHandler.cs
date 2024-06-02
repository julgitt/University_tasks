using ChainOfResponsibility.Requests;

namespace ChainOfResponsibility.Handlers
{
    public class OrderHandler : Handler
    {
        public override bool ProcessRequest(Request request)
        {
            if (request.messageType == "order")
            {
                Console.WriteLine("Processing order message");
            }
            return false;
        }
    }
}
