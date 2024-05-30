using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lista7.ViewModels.Classes.Notifications
{
    internal class CategorySelectedNotification
    {
        public string category;
        public CategorySelectedNotification(string category)
        {
            this.category = category;
        }
    }
}
