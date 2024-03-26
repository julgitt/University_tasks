using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad2
{

    public interface IShapeFactoryWorker
    {
        bool AcceptsParameters(string name, params object[] parameters);
        IShape Create(params object[] parameters);
    }

    public class RectangleWorker : IShapeFactoryWorker
    {
        public bool AcceptsParameters(string name, params object[] parameters)
        {
            bool properName = name == "Rectangle";
            bool properArgLength = parameters.Length == 2;
            bool properType = parameters[0] is int && parameters[1] is int;

            return properName && properArgLength && properType;
        }

        public IShape Create(params object[] parameters)
        {
            return new Rectangle((int)parameters[0], (int)parameters[1]);
        }
    }

    public class SquareWorker : IShapeFactoryWorker
    {
        public bool AcceptsParameters(string name, params object[] parameters)
        {
            bool properName = name == "Square";
            bool properArgLength = parameters.Length == 1;
            bool properType = parameters[0] is int;

            return properName && properArgLength && properType;
        }

        public IShape Create(params object[] parameters)
        {
            return new Square((int)parameters[0]);
        }
    }
}
