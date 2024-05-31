using Lista7.Models;

namespace Lista7.Repositories
{
    public class TeachersRepository
    {
        private List<Teacher> _teachers;
        private static int _nextId = 1;

        public TeachersRepository()
        {
            _teachers = new List<Teacher>();
        }

        public IEnumerable<Teacher> GetAllTeachers()
        {
            return new List<Teacher>(_teachers);
        }

        public Teacher GetTeacherById(int id)
        {
            Teacher? teacher = _teachers.Find(teacher => teacher.Id == id);
            if (teacher == null)
            {
                throw new Exception("Teacher not found for given id");
            }

            return teacher;
        }

        public void UpdateStudent(Teacher teacher)
        {
            if (teacher == null)
            {
                throw new ArgumentNullException(nameof(teacher), "Teacher cannot be null.");
            }

            var existingTeacher = _teachers.Find(s => s.Id == teacher.Id);
            if (existingTeacher != null)
            {
                existingTeacher.Name = teacher.Name;
                existingTeacher.Age = teacher.Age;
            }
        }

        public void AddTeacher(Teacher teacher)
        {
            if (teacher == null)
            {
                throw new ArgumentNullException(nameof(teacher), "Teacher cannot be null.");
            }

            teacher.Id = _nextId++;
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
