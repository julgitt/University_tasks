namespace ChainOfResponsibility.Requests
{
    public class Request
    {
        public string title;
        public string content;
        public string? messageType;

        public Request(string title, string content)
        {
            this.title = title;
            this.content = content;
        }
    }
}