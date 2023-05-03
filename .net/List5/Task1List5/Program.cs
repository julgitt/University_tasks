using System;
using BenchmarkDotNet.Attributes;
using BenchmarkDotNet.Running;

namespace Task1List5
{
    /*
     * 
    |           Method |       Mean |     Error |    StdDev |     Median |
    |----------------- |-----------:|----------:|----------:|-----------:|
    | DoWork1Benchmark |  0.0002 ns | 0.0008 ns | 0.0007 ns |  0.0000 ns |
    | DoWork2Benchmark | 13.9766 ns | 0.0742 ns | 0.0657 ns | 13.9688 ns |
    | DoWork3Benchmark |  0.0212 ns | 0.0125 ns | 0.0111 ns |  0.0216 ns |
    | DoWork4Benchmark | 43.0968 ns | 0.6755 ns | 0.8042 ns | 43.0086 ns |
     * */
    public class MyBenchmark
    {
        [Benchmark]
        public void DoWork1Benchmark()
        {
            int result = DoWork1(2, 3);
        }

        [Benchmark]
        public void DoWork2Benchmark()
        {
            dynamic result = DoWork2(2, 3);
        }

        [Benchmark]
        public void DoWork3Benchmark()
        {
            int result = DoWork3(3, 5);
        }
    
        [Benchmark]
        public void DoWork4Benchmark()
        {
            dynamic result = DoWork4(3, 5);
        }

        public int DoWork1(int x, int y)
        {
            return x + y;
        }

        public dynamic DoWork2(dynamic x, dynamic y)
        {
            return x + y;
        }
        public int DoWork3(int x, int y)
        {
            return (int)Math.Pow(x, y);
        }

        public dynamic DoWork4(dynamic x, dynamic y)
        {
            return Math.Pow(x,y);
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            var summary = BenchmarkRunner.Run<MyBenchmark>();
        }
    }
}
