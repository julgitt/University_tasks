using Lista7.Models.Interfaces;

namespace Lista7.Models
{
    public class Student : IUser
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public int Age { get; set; }
    }
}
