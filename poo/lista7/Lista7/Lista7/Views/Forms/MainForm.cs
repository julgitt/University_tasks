using Lista7.Repositories;
using Lista7.ViewModels;
using Lista7.ViewModels.Classes;
using Lista7.ViewModels.Classes.Notifications;
using Microsoft.VisualBasic.ApplicationServices;
using System.Security.Cryptography.X509Certificates;

namespace Lista7
{
    public partial class MainForm : Form
    {
        private UserDataGrid _userDataGrid;
        private StudentsRepository _students;
        private TeachersRepository _teachers;
        private EventAggregator _eventAggregator;

        public MainForm()
        {
            InitializeComponent();
            InitializeUserDataGrid();
            _eventAggregator = new EventAggregator();
            RegisterSubscribers(_eventAggregator);
        }


        private void InitializeUserDataGrid()
        {
            _students = new StudentsRepository();
            _students.AddStudent(new Models.Student { Id = 1, Age = 20, Name = "Jan Kowalski" });
            _students.AddStudent(new Models.Student { Id = 2, Age = 21, Name = "Ola Nowak" });
            _teachers = new TeachersRepository();
            _teachers.AddTeacher(new Models.Teacher { Id = 1, Age = 40, Name = "Bo¿ydar Adamski" });
            _teachers.AddTeacher(new Models.Teacher { Id = 2, Age = 46, Name = "Ignacy B³oniewski" });
            _userDataGrid = new UserDataGrid(dataGridView1, _students, _teachers); // dataGridViewUsers to DataGridView na formie
        }

        private void RegisterSubscribers(EventAggregator eventAggregator)
        {
            EventAggregator.AddSubscriber<CategorySelectedNotification>(_userDataGrid);
            EventAggregator.AddSubscriber<UserSelectedNotification>(_userDataGrid);
        }

        private void treeViewCategories_AfterSelect(object sender, TreeViewEventArgs e)
        {
            if (e.Node.Tag is string category)
            {
                EventAggregator.Publish(new CategorySelectedNotification(category));
            }
        }

        private void treeViewUsers_SelectedIndexChanged(object sender, TreeViewEventArgs e)
        {
            int id;
            bool isNumeric = int.TryParse(e.Node.Tag as string, out id);
            if (isNumeric)
            {
                if (e.Node.Parent.Tag is string category)
                    EventAggregator.Publish(new UserSelectedNotification(id, category));
            }
        }
    }
}