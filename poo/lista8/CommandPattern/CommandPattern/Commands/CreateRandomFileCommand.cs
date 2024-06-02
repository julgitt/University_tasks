using CommandPattern.Receivers;

namespace CommandPattern.Commands
{
    public class CreateRandomFileCommand : ICommand
    {
        private readonly Receiver _receiver;
        private readonly string _filename;

        public CreateRandomFileCommand(Receiver receiver, string filename)
        {
            _receiver = receiver;
            _filename = filename;
        }

        public void Execute()
        {
            _receiver.CreateRandomFile(_filename);
        }
    }
}
