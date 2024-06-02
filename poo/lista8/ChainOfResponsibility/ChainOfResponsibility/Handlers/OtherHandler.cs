using ChainOfResponsibility.Requests;

namespace ChainOfResponsibility.Handlers
{
    public class OtherHandler : Handler
    {
        public override bool ProcessRequest(Request request)
        {
            if (request.messageType == "other")
            {
                Console.WriteLine("Processing other message");
            }
            return false;
        }
    }
}
