using ChainOfResponsibility.Requests;

namespace ChainOfResponsibility.Handlers
{
    public class PraiseHandler : Handler
    {
        public override bool ProcessRequest(Request request)
        {
            if (request.messageType == "praise")
            {
                Console.WriteLine("Processing praise message");
            }
            return false;
        }
    }
}
