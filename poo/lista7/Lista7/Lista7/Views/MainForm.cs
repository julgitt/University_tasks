using Lista7.Infrastructure;
using Lista7.Infrastructure.Notifications;
using Lista7.Models;
using Lista7.Repositories;
using Lista7.ViewModels;

namespace Lista7.Views
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
            InitializeStudentsRepository();
            InitializeTeachersRepository();
            _eventAggregator = new EventAggregator();

            _userDataGrid = new UserDataGrid(dataGridView1, _students, _teachers, _eventAggregator); // dataGridViewUsers to DataGridView na formie
            InitializeTreeView();
        }

        private void InitializeStudentsRepository()
        {
            _students = new StudentsRepository();
            _students.AddStudent(new Models.Student { Id = 1, Age = 20, Name = "Jan Kowalski" });
            _students.AddStudent(new Models.Student { Id = 2, Age = 21, Name = "Ola Nowak" });

        }

        private void InitializeTeachersRepository()
        {
            _teachers = new TeachersRepository();
            _teachers.AddTeacher(new Models.Teacher { Id = 1, Age = 40, Name = "Bo¿ydar Adamski" });
            _teachers.AddTeacher(new Models.Teacher { Id = 2, Age = 46, Name = "Ignacy B³oniewski" });
        }

        private void InitializeTreeView()
        {
            var studentsNode = new TreeNode("Studenci")
            {
                Name = "students",
                Tag = UserCategory.Students
            };

            foreach (var student in _students.GetAllStudents())
            {
                var studentNode = new TreeNode(student.Name)
                {
                    Name = student.Name,
                    Tag = new UserTag(UserCategory.Students, student.Id)
                };
                studentsNode.Nodes.Add(studentNode);
            }

            var teachersNode = new TreeNode("Wyk³adowcy")
            {
                Name = "teachers",
                Tag = UserCategory.Teachers
            };

            foreach (var teacher in _teachers.GetAllTeachers())
            {
                var teacherNode = new TreeNode(teacher.Name)
                {
                    Name = teacher.Name,
                    Tag = new UserTag(UserCategory.Teachers, teacher.Id)
                };
                teachersNode.Nodes.Add(teacherNode);
            }

            treeView1.Nodes.Add(studentsNode);
            treeView1.Nodes.Add(teachersNode);
        }


        private void treeViewCategories_AfterSelect(object sender, TreeViewEventArgs e)
        {
            if (e.Node.Tag is UserCategory category)
            {
                _eventAggregator.Publish(new CategorySelectedNotification(category));
            }
        }

        private void treeViewUsers_SelectedIndexChanged(object sender, TreeViewEventArgs e)
        {
            if (e.Node.Tag is UserTag tag)
            {
                _eventAggregator.Publish(new UserSelectedNotification(tag.Id, tag.UserCategory));
            }
        }
    }
}