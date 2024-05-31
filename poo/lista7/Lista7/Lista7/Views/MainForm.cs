using Lista7.Infrastructure;
using Lista7.Infrastructure.Notifications;
using Lista7.Models;
using Lista7.Models.Interfaces;
using Lista7.Repositories;
using Lista7.ViewModels;

namespace Lista7.Views
{
    public partial class MainForm : Form
    {
        private UserDataGrid _userDataGrid;
        private UserTreeView _userTreeView;
        private StudentsRepository _students;
        private TeachersRepository _teachers;
        private EventAggregator _eventAggregator;

        public MainForm()
        {
            InitializeComponent();
            InitializeStudentsRepository();
            InitializeTeachersRepository();
            _eventAggregator = new EventAggregator();

            _userDataGrid = new UserDataGrid(dataGridView1, _students, _teachers, _eventAggregator);

            _userTreeView = new UserTreeView(treeView1, _eventAggregator);
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
                _eventAggregator.Publish(new UserSelectedNotification(tag.id, tag.userCategory));
            }
        }

        private void button_change_Click(object sender, EventArgs e)
        {
            var selectedNode = treeView1.SelectedNode;
            if (selectedNode == null || !(selectedNode.Tag is UserTag userTag))
            {
                MessageBox.Show("Proszê wybraæ u¿ytkownika w drzewie.");
                return;
            }

            var category = userTag.userCategory;
            var id = userTag.id;
          
            ModifyUser(category, id);
        }

        private void button_add_Click(object sender, EventArgs e)
        {
            var selectedNode = treeView1.SelectedNode;
            if (selectedNode == null || !(selectedNode.Tag is UserCategory category))
            {
                MessageBox.Show("Proszê wybraæ kategoriê w drzewie.");
                return;
            }

            AddUser(category);
        }

        private void AddUser(UserCategory category)
        {
            using (var addUserForm = new UserForm())
            {
                if (addUserForm.ShowDialog() == DialogResult.OK)
                {
                    var newUserName = addUserForm.UserName;
                    var newUserAge = addUserForm.Age;
                    var id = 0;
                    if (category == UserCategory.Students)
                    {
                        var newStudent = new Student { Name = newUserName, Age = newUserAge };
                        _students.AddStudent(newStudent);
                        id = newStudent.Id;
                    }
                    else if (category == UserCategory.Teachers)
                    {
                        var newTeacher = new Teacher { Name = newUserName, Age = newUserAge };
                        _teachers.AddTeacher(newTeacher);
                        id = newTeacher.Id;
                    }

                    _eventAggregator.Publish(new UserAddedNotification(id, category, newUserName, newUserAge));
                    _eventAggregator.Publish(new CategorySelectedNotification(category));
                }
            }
        }

        private void ModifyUser(UserCategory category, int userId)
        {
            IUser oldUser = (category == UserCategory.Students) ? _students.GetStudentById(userId) : _teachers.GetTeacherById(userId);

            using (var modifyUserForm = new UserForm(oldUser.Name, oldUser.Age))
            {
                if (modifyUserForm.ShowDialog() == DialogResult.OK)
                {
                    var updatedUserName = modifyUserForm.UserName;
                    var updatedUserAge = modifyUserForm.Age;

                    if (category == UserCategory.Students)
                    {
                        var newStudent = new Student { Id = userId, Name = updatedUserName, Age = updatedUserAge };
                        _students.UpdateStudent(newStudent);
                    }
                    else if (category == UserCategory.Teachers)
                    {
                        var newTeacher = new Teacher { Id = userId, Name = updatedUserName, Age = updatedUserAge };
                        _teachers.AddTeacher(newTeacher);
                    }

                    _eventAggregator.Publish(new UserModifiedNotification(userId, category, updatedUserName, updatedUserAge));
                    _eventAggregator.Publish(new UserSelectedNotification(userId, category));
                }
            }
        }
    }
}