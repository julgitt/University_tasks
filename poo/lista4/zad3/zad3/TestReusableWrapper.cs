using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Zad3;

namespace zad3
{
    [TestClass]
    public class TestReusableWrapper
    {
        [TestMethod]
        public void CreateReusable()
        {
            var reusable = new ReusableWrapper();

            reusable.DoWork();
            reusable.Release();
        }

        [TestMethod]
        public void CapacityDepleted()
        {
            var reusable = new ReusableWrapper();

            Assert.ThrowsException<ArgumentException>(
                () =>
                {
                    var reusable2 = new ReusableWrapper();
                });
            reusable.Release();
        }

        [TestMethod]
        public void ReusedObject()
        {
            var reusable = new ReusableWrapper();

            reusable.Release();

            var reusable2 = new ReusableWrapper();
            Assert.AreEqual(reusable, reusable2);
        }

        [TestMethod]
        public void ReturnedObjectRoWork()
        {
            ReusableWrapper reusable = new ReusableWrapper();

            reusable.Release();
            Assert.ThrowsException<ArgumentException>(
                () =>
                {
                    reusable.DoWork();
                });
        }
    }
}
