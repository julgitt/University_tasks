using ChainOfResponsibility.Handlers;
using ChainOfResponsibility.Requests;

namespace ChainOfResponsibility
{
    class Program
    {
        static void Main()
        {
            var handlersChain = new ClassifierHandler();
            handlersChain.AttachHandler(new InvalidHandler());
            handlersChain.AttachHandler(new PraiseHandler());
            handlersChain.AttachHandler(new ComplaintHandler());
            handlersChain.AttachHandler(new OrderHandler());
            handlersChain.AttachHandler(new OtherHandler());
            handlersChain.AttachHandler(new ArchiveHandler());

            var requestMessages = new[]
            {
                new Request("Order XYZ", "This is an order for product XYZ"),
                new Request("Praise", "Good job!"),
                new Request("Complaint", "I have a complaint about your service."),
                new Request("Other", "Example message"),
                new Request("Too Short - invalid", ""),
                new Request("Too Long - invalid", new string('x', 1001))
            };

            foreach (var request in requestMessages)
            {
                handlersChain.DispatchRequest(request);
            }
        }
    }
}