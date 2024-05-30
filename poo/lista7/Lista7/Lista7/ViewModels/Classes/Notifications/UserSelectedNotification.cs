using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lista7.ViewModels.Classes.Notifications
{
    internal class UserSelectedNotification
    {
        public int id;
        public string type;
        public UserSelectedNotification(int id, string type)
        {
            this.id = id;
            this.type = type;
        }
    }
}
