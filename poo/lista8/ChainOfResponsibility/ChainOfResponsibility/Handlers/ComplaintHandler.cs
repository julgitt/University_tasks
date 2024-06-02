using ChainOfResponsibility.Requests;

namespace ChainOfResponsibility.Handlers
{
    public class ComplaintHandler : Handler
    {
        public override bool ProcessRequest(Request request)
        {
            if (request.messageType == "complaint")
            {
                Console.WriteLine("Processing complaint message");
            }
            return false;
        }
    }
}
