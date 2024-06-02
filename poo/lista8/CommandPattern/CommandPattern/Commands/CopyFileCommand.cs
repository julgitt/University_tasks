using CommandPattern.Receivers;

namespace CommandPattern.Commands
{
    public class CopyFileCommand : ICommand
    {
        private readonly Receiver _receiver;
        private readonly string _src;
        private readonly string _dest;

        public CopyFileCommand(Receiver receiver, string src, string dest)
        {
            _receiver = receiver;
            _src = src;
            _dest = dest;
        }

        public void Execute()
        {
            _receiver.CopyFile(_src, _dest);
        }
    }
}
