using Lista7.Models;

namespace Lista7.Infrastructure.Notifications
{
    internal class UserSelectedNotification
    {
        public int Id { get; }
        public UserCategory Category { get; }

        public UserSelectedNotification(int id, UserCategory category)
        {
            this.Id = id;
            this.Category = category;
        }
    }
}
