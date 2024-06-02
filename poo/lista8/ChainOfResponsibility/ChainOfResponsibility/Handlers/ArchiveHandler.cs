using ChainOfResponsibility.Requests;

namespace ChainOfResponsibility.Handlers
{
    internal class ArchiveHandler : Handler
    {
        public override bool ProcessRequest(Request request)
        {
            Console.WriteLine($"Archiving message: {request.title}");
            return true;
        }
    }
}
