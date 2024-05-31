using Lista7.Repositories;
using Lista7.Models;
using Lista7.Infrastructure.Notifications;
using Lista7.Infrastructure.Interfaces;
    
namespace Lista7.ViewModels
{
    public partial class UserDataGrid :
        ISubscriber<CategorySelectedNotification>,
        ISubscriber<UserSelectedNotification>
    {
        private DataGridView _dataGridView;
        private StudentsRepository _studentsRepository;
        private TeachersRepository _teachersRepository;
        private IEventAggregator _eventAggregator;

        public UserDataGrid(DataGridView grid, StudentsRepository students, TeachersRepository teachers, IEventAggregator eventAggregator)
        {
            _dataGridView = grid;
            _studentsRepository = students;
            _teachersRepository = teachers;
            _eventAggregator = eventAggregator;

            _eventAggregator.AddSubscriber<CategorySelectedNotification>(this);
            _eventAggregator.AddSubscriber<UserSelectedNotification>(this);
        }

        void ISubscriber<CategorySelectedNotification>.Handle(CategorySelectedNotification notification)
        {
            switch (notification.Category)
            {
                case UserCategory.Students:
                    UpdateDataGrid(_studentsRepository.GetAllStudents().ToList());
                    break;
                case UserCategory.Teachers:
                    UpdateDataGrid(_teachersRepository.GetAllTeachers().ToList());
                    break;
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }

        void ISubscriber<UserSelectedNotification>.Handle(UserSelectedNotification notification)
        {
            switch (notification.Category)
            {
                case UserCategory.Students:
                    UpdateDataGrid(new List<Student> { _studentsRepository.GetStudentById(notification.Id) });
                    break;
                case UserCategory.Teachers:
                    UpdateDataGrid(new List<Teacher> { _teachersRepository.GetTeacherById(notification.Id) });
                    break;
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }

        private void UpdateDataGrid<T>(List<T> data)
        {
            if (_dataGridView.InvokeRequired)
            {
                _dataGridView.Invoke(new Action(() => _dataGridView.DataSource = data));
            }
            else
            {
                _dataGridView.DataSource = data;
            }
        }
    }
}
