using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Zad2;

namespace zad2
{
    [TestClass]
    public class UnitTests
    {
        [TestMethod]
        public void TestSquare()
        {
            ShapeFactory factory = new ShapeFactory();
            factory.RegisterWorker(new SquareWorker());
            int size = 4;
            IShape square = factory.CreateShape("Square", size);
            int properArea = size * size;
            int area = square.GetArea();

            Assert.AreEqual(area, properArea);
        }

        [TestMethod]
        public void TestRectangle()
        {
            ShapeFactory factory = new ShapeFactory();
            factory.RegisterWorker(new RectangleWorker());
            int width = 4;
            int height = 5;
            IShape rectangle = factory.CreateShape("Rectangle", width, height);
            int properArea = width * height;
            int area = rectangle.GetArea();

            Assert.AreEqual(area, properArea);
        }

        [TestMethod]
        public void TestCompareDifferentShapes()
        {
            ShapeFactory factory = new ShapeFactory();
            factory.RegisterWorker(new SquareWorker());
            factory.RegisterWorker(new RectangleWorker());
            int width = 4;
            int height = 5;
            IShape rectangle = factory.CreateShape("Rectangle", width, height);
            IShape square = factory.CreateShape("Square", width);

            Assert.AreNotEqual(rectangle, square);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void TestNotRegisteredShape()
        {
            ShapeFactory factory = new ShapeFactory();
            int width = 4;
            int height = 5;
            IShape rectangle = factory.CreateShape("Rectangle", width, height);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void TestWrongNumberOfParameters()
        {
            ShapeFactory factory = new ShapeFactory();
            int width = 4;
            int height = 5;
            IShape rectangle = factory.CreateShape("Rectangle", width, height, width, height);
        }
    }
}
