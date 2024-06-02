
using CommandPattern.Commands;
using CommandPattern.Invokers;
using CommandPattern.Receivers;

namespace CommandPattern
{
    class Program
    {
        static async Task Main(string[] args)
        {
            var receiver = new Receiver();
            var invoker = new Invoker();

            invoker.StartWorkers(2);

            invoker.AddCommand(new FTPDownloadCommand(receiver, "example.txt"));
            invoker.AddCommand(new HTTPDownloadCommand(receiver, "file.txt"));
            invoker.AddCommand(new CreateRandomFileCommand(receiver, "random.txt"));
            invoker.AddCommand(new CopyFileCommand(receiver, "source.txt", "destination.txt"));

            await Task.Delay(5000);

            invoker.StopWorkers();
        }
    }
}
