using CommandPattern.Receivers;

namespace CommandPattern.Commands
{
    public class FTPDownloadCommand : ICommand
    {
        private readonly Receiver _receiver;
        private readonly string _filename;

        public FTPDownloadCommand(Receiver receiver, string filename)
        {
            _receiver = receiver;
            _filename = filename;
        }

        public void Execute()
        {
            _receiver.DownloadFTP(_filename);
        }
    }
}
