namespace Lista7.Models
{
    public class UserTag
    {
        public UserCategory UserCategory { get; set; }
        public int Id { get; set; }

        public UserTag(UserCategory userCategory, int id)
        {
            UserCategory = userCategory;
            Id = id;
        }
    }
}
