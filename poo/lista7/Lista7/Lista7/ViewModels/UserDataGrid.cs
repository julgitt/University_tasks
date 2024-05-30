using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lista7.ViewModels.Classes.Notifications;
using Lista7.Repositories;
using Lista7.Models;
using Lista7.ViewModels.Interfaces;
using Lista7.ViewModels.Classes;
using Microsoft.VisualBasic.ApplicationServices;

namespace Lista7.ViewModels
{
    public partial class UserDataGrid :
        ISubscriber<CategorySelectedNotification>, ISubscriber<UserSelectedNotification>
    {
        private DataGridView _dataGridView;
        private StudentsRepository _studentsRepository;
        private TeachersRepository _teachersRepository;
           
        public UserDataGrid(DataGridView grid, StudentsRepository students, TeachersRepository teachers )
        {
            _dataGridView = grid;
            _studentsRepository = students;
            _teachersRepository = teachers;
        }

        void ISubscriber<CategorySelectedNotification>.Handle(CategorySelectedNotification notification)
        {
            var selectedCategory = notification.category;
            if (selectedCategory == "students") {
                _dataGridView.DataSource = _studentsRepository.GetAllStudents();
            } else if (selectedCategory == "teachers")
            {
                _dataGridView.DataSource = _teachersRepository.GetAllTeachers();
            }
        }

        void ISubscriber<UserSelectedNotification>.Handle(UserSelectedNotification notification)
        {
            var userType = notification.type;
            var userId = notification.id;
            if (userType == "students")
            {
                _dataGridView.DataSource = new[] { _studentsRepository.GetStudentById(userId) };
            }
            else if (userType == "teachers")
            {
                _dataGridView.DataSource = new[] { _teachersRepository.GetTeacherById(userId) };
            }
        }
    }

}
