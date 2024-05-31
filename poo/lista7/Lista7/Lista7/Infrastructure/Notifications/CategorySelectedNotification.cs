using Lista7.Models;

namespace Lista7.Infrastructure.Notifications
{
    internal class CategorySelectedNotification
    {
        public UserCategory Category{ get; }

        public CategorySelectedNotification(UserCategory category)
        {
            this.Category = category;
        }
    }
}
