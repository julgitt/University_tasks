using System.Security.AccessControl;
using System.Xml.Linq;

namespace Zad2
{
    public class ShapeFactory
    {
        private List<IShapeFactoryWorker> _workers = new List<IShapeFactoryWorker>();
        public void RegisterWorker(IShapeFactoryWorker worker)
        {
            _workers.Add(worker);
        }

        public IShape CreateShape(string shapeName, params object[] parameters)
        {
            foreach (var worker in _workers)
            {
                if (worker.AcceptsParameters(shapeName, parameters))
                    return worker.Create(parameters);
            }
            throw new ArgumentException(string.Format("Couldn't find {0} factory worker", shapeName));
        }
    }

}