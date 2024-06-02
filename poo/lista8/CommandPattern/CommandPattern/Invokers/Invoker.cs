using System.Collections.Concurrent;
using CommandPattern.Commands;

namespace CommandPattern.Invokers
{
    public class Invoker
    {
        private readonly BlockingCollection<ICommand> _queue = new BlockingCollection<ICommand>();
        private Thread[] _threads;

        public void AddCommand(ICommand command)
        {
            _queue.Add(command);
        }

        public void StartWorkers(int workerCount)
        {
            _threads = new Thread[workerCount];
            for (int i = 0; i < workerCount; i++)
            {
                _threads[i] = new Thread(Worker);
                _threads[i].Start();
            }
        }

        public void StopWorkers()
        {
            _queue.CompleteAdding();
            foreach (var thread in _threads)
            {
                thread.Join();
            }
        }

        private void Worker()
        {
            foreach (var command in _queue.GetConsumingEnumerable())
            {
                command.Execute();
            }
        }
    }
}
