using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Lista7.Models;
using System.Threading.Tasks;

namespace Lista7.Repositories
{
    public class StudentsRepository
    {
        private List<Student> _students;

        public StudentsRepository()
        {
            _students = new List<Student>();
        }

        public IEnumerable<Student> GetAllStudents()
        {
            return _students;
        }

        public Student GetStudentById(int id)
        {
            return _students.Find(student => student.Id == id);
        }

        public void AddStudent(Student student)
        {
            _students.Add(student);
        }

        public void DeleteStudent(int id)
        {
            var student = _students.Find(s => s.Id == id);
            if (student != null)
            {
                _students.Remove(student);
            }
        }
    }
}
