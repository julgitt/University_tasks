using Lista7.Models;

namespace Lista7.Repositories
{
    public class StudentsRepository
    {
        private List<Student> _students;
        private static int _nextId = 1;

        public StudentsRepository()
        {
            _students = new List<Student>();
        }

        public IEnumerable<Student> GetAllStudents()
        {
            return new List<Student>(_students);
        }

        public Student GetStudentById(int id)
        {
            Student? student = _students.Find(student => student.Id == id);
            if (student == null)
            {
                throw new Exception("Student not found for given id");
            }

            return student;
        }

        public void UpdateStudent(Student student)
        {
            if (student == null)
            {
                throw new ArgumentNullException(nameof(student), "Student cannot be null.");
            }

            var existingStudent = _students.Find(s => s.Id == student.Id);
            if (existingStudent != null)
            {
                existingStudent.Name = student.Name;
                existingStudent.Age = student.Age;
            }
        }

        public void AddStudent(Student student)
        {
            if (student == null)
            {
                throw new ArgumentNullException(nameof(student), "Student cannot be null.");
            }
            student.Id = _nextId++;
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
