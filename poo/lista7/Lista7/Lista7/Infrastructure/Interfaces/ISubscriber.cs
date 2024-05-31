namespace Lista7.Infrastructure.Interfaces
{
    public interface ISubscriber<T>
    {
        public void Handle(T notification);
    }
}
