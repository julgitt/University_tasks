using Lista7.Repositories;
using Lista7.Models;
using Lista7.Infrastructure.Notifications;
using Lista7.Infrastructure.Interfaces;

namespace Lista7.ViewModels
{
    public partial class UserTreeView :
     ISubscriber<UserModifiedNotification>,
     ISubscriber<UserAddedNotification>
    {
        private TreeView _treeView;
        private IEventAggregator _eventAggregator;
         
        public UserTreeView(TreeView tree, IEventAggregator eventAggregator)
        {
            _treeView = tree;
            _eventAggregator = eventAggregator;

            _eventAggregator.AddSubscriber<UserModifiedNotification>(this);
            _eventAggregator.AddSubscriber<UserAddedNotification>(this);
        }

        void ISubscriber<UserModifiedNotification>.Handle(UserModifiedNotification notification)
        {
            var parentNode = _treeView.Nodes.Find(notification.Category.ToString().ToLower(), true).FirstOrDefault();
            if (parentNode != null)
            {
                var node = parentNode.Nodes.Cast<TreeNode>().FirstOrDefault(n => (n.Tag as UserTag)?.id == notification.Id);
                if (node != null)
                {
                    node.Text = notification.Name;
                }
            }
        }

        void ISubscriber<UserAddedNotification>.Handle(UserAddedNotification notification)
        {
            var parentNode = _treeView.Nodes.Find(notification.Category.ToString().ToLower(), true).FirstOrDefault();
            if (parentNode != null)
            {
                parentNode.Nodes.Add(new TreeNode(notification.Name) { Tag = new UserTag(notification.Category, notification.Id) });
            }
        }
    }
}
