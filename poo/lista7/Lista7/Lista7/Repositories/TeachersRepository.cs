using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Lista7.Models;
namespace Lista7.Repositories
{
    public class TeachersRepository
    {
        private List<Teacher> _teachers;

        public TeachersRepository()
        {
            _teachers = new List<Teacher>();
        }

        public IEnumerable<Teacher> GetAllTeachers()
        {
            return _teachers;
        }

        public Teacher GetTeacherById(int id)
        {
            return _teachers.Find(teacher => teacher.Id == id);
        }

        public void AddTeacher(Teacher teacher)
        {
            _teachers.Add(teacher);
        }

        public void DeleteTeacher(int id)
        {
            var teacher = _teachers.Find(t => t.Id == id);
            if (teacher != null)
            {
                _teachers.Remove(teacher);
            }
        }
    }
}
