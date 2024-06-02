using CommandPattern.Receivers;

namespace CommandPattern.Commands
{
    public class HTTPDownloadCommand : ICommand
    {
        private readonly Receiver _receiver;
        private readonly string _filename;

        public HTTPDownloadCommand(Receiver receiver, string filename)
        {
            _receiver = receiver;
            _filename = filename;
        }

        public void Execute()
        {
            _receiver.DownloadHTTP(_filename);
        }
    }
}
