
namespace Lista7.Infrastructure.Interfaces
{
    public interface ISubscriber<T>
    {
        void Handle(T notification);
    }
}
