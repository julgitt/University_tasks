using Lista7.Models;

namespace Lista7.Infrastructure.Notifications
{
    internal class UserModifiedNotification
    {
        public int Id { get; }
        public UserCategory Category { get; }
        public string? Name { get; }
        public int Age { get; }

        public UserModifiedNotification(int id, UserCategory category, string? name, int age)
        {
            Id = id;
            Category = category;
            Name = name;
            Age = age;
        }
    }
}
