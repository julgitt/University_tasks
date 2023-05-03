
// C:\Users\Julia\source\repos\Task4_List1\Task4_List1\dekompilat.exe
// Task4_List1, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// Global type: <Module>
// Entry point: Task1_List1.Program.Main
// Architecture: AnyCPU (64-bit preferred)
// Runtime: v4.0.30319
// Hash algorithm: SHA1

using System;
using System.Diagnostics;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Runtime.Versioning;
using Microsoft.CodeAnalysis;

[assembly: Debuggable(DebuggableAttribute.DebuggingModes.Default | DebuggableAttribute.DebuggingModes.DisableOptimizations | DebuggableAttribute.DebuggingModes.IgnoreSymbolStoreSequencePoints | DebuggableAttribute.DebuggingModes.EnableEditAndContinue)]
[assembly: AssemblyTitle("Task4_List1")]
[assembly: CompilationRelaxations(8)]
[assembly: RuntimeCompatibility(WrapNonExceptionThrows = true)]
[assembly: TargetFramework(".NETCoreApp,Version=v6.0", FrameworkDisplayName = ".NET 6.0")]
[assembly: AssemblyCompany("Task4_List1")]
[assembly: AssemblyConfiguration("Debug")]
[assembly: AssemblyFileVersion("1.0.0.0")]
[assembly: AssemblyInformationalVersion("1.0.0")]
[assembly: AssemblyProduct("Task4_List1")]
[assembly: AssemblyVersion("1.0.0.0")]
namespace Microsoft.CodeAnalysis
{
	[CompilerGenerated]
	[Microsoft.CodeAnalysis.Embedded]
	internal sealed class EmbeddedAttribute : Attribute
	{
	}
}
namespace System.Runtime.CompilerServices
{
	[Microsoft.CodeAnalysis.Embedded]
	[CompilerGenerated]
	[AttributeUsage(AttributeTargets.Class | AttributeTargets.Property | AttributeTargets.Field | AttributeTargets.Event | AttributeTargets.Parameter | AttributeTargets.ReturnValue | AttributeTargets.GenericParameter, AllowMultiple = false, Inherited = false)]
	internal sealed class NullableAttribute : Attribute
	{
		public readonly byte[] NullableFlags;

		public NullableAttribute(byte A_0)
		{
			NullableFlags = new byte[1] { A_0 };
		}

		public NullableAttribute(byte[] A_0)
		{
			NullableFlags = A_0;
		}
	}
	[CompilerGenerated]
	[AttributeUsage(AttributeTargets.Class | AttributeTargets.Struct | AttributeTargets.Method | AttributeTargets.Interface | AttributeTargets.Delegate, AllowMultiple = false, Inherited = false)]
	[Microsoft.CodeAnalysis.Embedded]
	internal sealed class NullableContextAttribute : Attribute
	{
		public readonly byte Flag;

		public NullableContextAttribute(byte A_0)
		{
			Flag = A_0;
		}
	}
}
namespace Task1_List1
{
	public class Example
	{
		private int[] array;

		public int this[int i]
		{
			get
			{
				return array[i];
			}
			set
			{
				array[i] = value;
			}
		}

		public int numberOfElements => array.Length;

		public Example()
		{
			array = new int[1] { 1 };
		}

		public Example(params int[] input)
		{
			array = new int[input.Length];
			for (int i = 0; i < input.Length; i++)
			{
				array[i] = input[i];
			}
		}

		public void printArray()
		{
			for (int i = 0; i < array.Length; i++)
			{
				Console.WriteLine(array[i]);
			}
		}
	}
	public delegate void PerformCalculation(int x, int y);
	public class Calculation
	{
		public void printAdd(int x, int y)
		{
			Console.WriteLine(x + y);
		}

		public void printSub(int x, int y)
		{
			Console.WriteLine(x - y);
		}
	}
	public delegate void Notify();
	public class EventExample
	{
		public event Notify ProcessCompleted;

		public void StartProcess()
		{
			Console.WriteLine("Process Started!");
			OnProcessCompleted();
		}

		protected virtual void OnProcessCompleted()
		{
			Console.WriteLine("Process Completed!");
			this.ProcessCompleted?.Invoke();
		}
	}
	internal class Program
	{
		private static void Main()
		{
			Calculation @object = new Calculation();
			PerformCalculation performCalculation = @object.printAdd;
			Console.WriteLine("Calling the delegate:");
			performCalculation(5, 5);
			Console.WriteLine("Event example:");
			EventExample eventExample = new EventExample();
			eventExample.StartProcess();
			Console.WriteLine("Example class with indexer:");
			Example example = new Example(1, 2, 3);
			Example example2 = new Example();
			example[0] = 4;
			example[1] = 5;
			for (int i = 0; i < example.numberOfElements; i++)
			{
				Console.WriteLine(example[i]);
			}
			Console.WriteLine("If with boolean variables:");
			bool flag = true;
			bool flag2 = false;
			if (flag)
			{
				Console.WriteLine(flag);
			}
			else
			{
				Console.WriteLine(flag2);
			}
			if (flag2)
			{
				Console.WriteLine(flag);
			}
			else
			{
				Console.WriteLine(flag2);
			}
			Console.WriteLine("Switch case:");
			switch (5)
			{
			case 1:
				Console.WriteLine("Case 1");
				break;
			case 2:
				Console.WriteLine("Case 2");
				break;
			case 3:
				Console.WriteLine("Case 3");
				break;
			default:
				Console.WriteLine("Case default");
				break;
			}
			Console.ReadLine();
		}
	}
}
