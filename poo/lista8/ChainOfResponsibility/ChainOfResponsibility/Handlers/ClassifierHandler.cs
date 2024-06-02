using ChainOfResponsibility.Requests;

namespace ChainOfResponsibility.Handlers
{
    public class ClassifierHandler : Handler
    {
        public override bool ProcessRequest(Request request)
        {
            if (string.IsNullOrEmpty(request.content))
            {
                request.messageType = "invalid";
            }
            else if (request.content.Length > 1000)
            {
                request.messageType = "invalid";
            }
            else if (request.content.ToLower().Contains("complaint") 
                || request.title.ToLower().Contains("complaint"))
            {
                request.messageType = "complaint";
            }
            else if (request.content.ToLower().Contains("order")
                || request.title.ToLower().Contains("order"))
            {
                request.messageType = "order";
            }
            else if (request.content.ToLower().Contains("praise")
                || request.title.ToLower().Contains("praise"))
            {
                request.messageType = "praise";
            }
            else
            {
                request.messageType = "other";
            }
            return false;
        }
    }
}
