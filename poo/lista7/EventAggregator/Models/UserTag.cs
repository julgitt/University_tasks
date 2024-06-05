namespace Lista7.Models
{
    public class UserTag
    {
        public UserCategory userCategory;
        public int id;

        public UserTag(UserCategory userCategory, int id)
        {
            this.userCategory = userCategory;
            this.id = id;
        }
    }
}
