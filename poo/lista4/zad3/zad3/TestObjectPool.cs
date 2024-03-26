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
    public class TestObjectPool
    {
        [TestMethod]
        public void InvalidCapacity()
        {
            Assert.ThrowsException<ArgumentException>(
                () =>
                {
                    ObjectPool pool = new ObjectPool(0);
                });
        }

        [TestMethod]
        public void ValidCapacity()
        {
            ObjectPool pool = new ObjectPool(1);
            Reusable reusable = pool.AcquireReusable();

            Assert.IsNotNull(reusable);
        }

        [TestMethod]
        public void CapacityDepleted()
        {
            ObjectPool pool = new ObjectPool(1);
            Reusable reusable = pool.AcquireReusable();

            Assert.ThrowsException<ArgumentException>(
                () =>
                {
                    Reusable reusable2 = pool.AcquireReusable();
                });
        }

        [TestMethod]
        public void ReusedObject()
        {
            ObjectPool pool = new ObjectPool(1);
            Reusable reusable = pool.AcquireReusable();

            pool.ReleaseReusable(reusable);

            Reusable reusable2 = pool.AcquireReusable();
            Assert.AreEqual(reusable, reusable2);
        }

        [TestMethod]
        public void ReleaseInvalideReusable()
        {
            ObjectPool pool = new ObjectPool(1);
            Reusable reusable = new Reusable();

            Assert.ThrowsException<ArgumentException> (
                () =>
                {
                    pool.ReleaseReusable(reusable);
                });
        }
    }
}
