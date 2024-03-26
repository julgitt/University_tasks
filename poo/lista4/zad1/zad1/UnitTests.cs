using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace zad1
{
    [TestClass]
    public class UnitTests
    {
        [TestMethod]
        public void TestProcessSingleton() 
        {
            ProcessSingleton s1 = ProcessSingleton.Instance();  
            ProcessSingleton s2 = ProcessSingleton.Instance();

            Assert.IsNotNull(s1);
            Assert.AreEqual(s1, s2); 
        }

        [TestMethod]
        public void TestProcessSingletonMultiThreading()
        {
            Thread t1, t2;
            ProcessSingleton s1 = null, s2 = null;

            t1 = new Thread(() =>
                {
                    s1 = ProcessSingleton.Instance();
                }
            );

            t2 = new Thread(() =>
                {
                    s2 = ProcessSingleton.Instance();
                }
            );

            t1.Start();
            t2.Start();
            t1.Join();
            t2.Join();


            Assert.IsNotNull(s1);
            Assert.AreEqual(s1, s2);
        }


        [TestMethod]
        public void TestThreadSingleton()
        {
            ThreadSingleton s1 = ThreadSingleton.Instance();
            ThreadSingleton s2 = ThreadSingleton.Instance();


            Assert.IsNotNull(s1);
            Assert.AreEqual(s1, s2);
        }

        [TestMethod]
        public void TestThreadSingletonMultiThreading()
        {
            Thread t1, t2;
            ThreadSingleton s1 = null, s2 = null;

            t1 = new Thread(() =>
                {
                    s1 = ThreadSingleton.Instance();
                }
            );

            t2 = new Thread(() =>
                {
                    s2 = ThreadSingleton.Instance();
                }
            );

            t1.Start();
            t2.Start();
            t2.Join();
            t1.Join();


            Assert.IsNotNull(s1);
            Assert.IsNotNull(s2);
            Assert.AreNotEqual(s1, s2);
        }


        [TestMethod]
        public void TestTimeSingleton()
        {
            TimeSingleton s1 = TimeSingleton.Instance();
            Thread.Sleep(TimeSpan.FromSeconds(4));
            TimeSingleton s2 = TimeSingleton.Instance();
            Thread.Sleep(TimeSpan.FromSeconds(2));
            TimeSingleton s3 = TimeSingleton.Instance();

            Assert.IsNotNull(s1);
            Assert.IsNotNull(s2);
            Assert.IsNotNull(s3);
            Assert.AreEqual(s1, s2);
            Assert.AreNotEqual(s1, s3);
        }
    }
}
