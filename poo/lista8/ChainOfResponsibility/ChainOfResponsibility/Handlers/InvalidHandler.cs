using ChainOfResponsibility.Requests;

namespace ChainOfResponsibility.Handlers
{
    internal class InvalidHandler : Handler
    {
        public override bool ProcessRequest(Request request)
        {
            if (request.messageType == "invalid")
            {
                Console.WriteLine("Processing invalid message");
            }
            return false;
        }
    }
}
