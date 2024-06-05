using System.ComponentModel;
using System.Diagnostics.Tracing;
using System.IO.Enumeration;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

public interface ILogger
{
    void Log(string Message);
}

public class NullLogger : ILogger
{
    public void Log(string message)
    {

    }
}

public class ConsoleLogger : ILogger
{
    public void Log(string message)
    {
        Console.WriteLine(message);
    }
}

public class FileLogger : ILogger
{
    string filename;

    public FileLogger(string filename)
    {
        this.filename = filename;
    }

    public void Log(string message)
    {
        File.AppendAllText(this.filename, message);
    }
}

public enum LogType { None, Console, File }

public class LoggerFactory
{
    private static readonly LoggerFactory instance = new LoggerFactory();

    public static LoggerFactory Instance
    {
        get { return instance; }
    }

    public ILogger GetLogger(LogType LogType, string Parameters = null)
    {
        switch (LogType)
        {
            case LogType.None:
                return new NullLogger();
            case LogType.Console:
                return new ConsoleLogger();
            case LogType.File:
                return new FileLogger(Parameters);
            default:
                throw new InvalidEnumArgumentException();
        }
    }

    public static void Main()
    {
        // klient:
        ILogger logger1 = LoggerFactory.Instance.GetLogger(LogType.File, @".\foo.txt");
        logger1.Log("foo bar\n"); // logowanie do pliku
        ILogger logger2 = LoggerFactory.Instance.GetLogger(LogType.Console);
        logger2.Log("bar\n"); // logowanie na konsole
        ILogger logger3 = LoggerFactory.Instance.GetLogger(LogType.None);
        logger3.Log("qux\n"); // brak logowania

    }
}