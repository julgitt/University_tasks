// C:\Users\Julia\source\repos\Task4_List1\Task4_List1\bin\Debug\net6.0\Task4_List1.dll

.assembly extern System.Runtime
{
	.publickeytoken = (
		b0 3f 5f 7f 11 d5 0a 3a
	)
	.ver 6:0:0:0
}
.assembly extern System.Console
{
	.publickeytoken = (
		b0 3f 5f 7f 11 d5 0a 3a
	)
	.ver 6:0:0:0
}
.assembly extern System.Threading
{
	.publickeytoken = (
		b0 3f 5f 7f 11 d5 0a 3a
	)
	.ver 6:0:0:0
}
.assembly Task4_List1
{
	.custom instance void [System.Runtime]System.Runtime.CompilerServices.CompilationRelaxationsAttribute::.ctor(int32) = (
		01 00 08 00 00 00 00 00
	)
	.custom instance void [System.Runtime]System.Runtime.CompilerServices.RuntimeCompatibilityAttribute::.ctor() = (
		01 00 01 00 54 02 16 57 72 61 70 4e 6f 6e 45 78
		63 65 70 74 69 6f 6e 54 68 72 6f 77 73 01
	)
	.custom instance void [System.Runtime]System.Diagnostics.DebuggableAttribute::.ctor(valuetype [System.Runtime]System.Diagnostics.DebuggableAttribute/DebuggingModes) = (
		01 00 07 01 00 00 00 00
	)
	.custom instance void [System.Runtime]System.Runtime.Versioning.TargetFrameworkAttribute::.ctor(string) = (
		01 00 18 2e 4e 45 54 43 6f 72 65 41 70 70 2c 56
		65 72 73 69 6f 6e 3d 76 36 2e 30 01 00 54 0e 14
		46 72 61 6d 65 77 6f 72 6b 44 69 73 70 6c 61 79
		4e 61 6d 65 08 2e 4e 45 54 20 36 2e 30
	)
	.custom instance void [System.Runtime]System.Reflection.AssemblyCompanyAttribute::.ctor(string) = (
		01 00 0b 54 61 73 6b 34 5f 4c 69 73 74 31 00 00
	)
	.custom instance void [System.Runtime]System.Reflection.AssemblyConfigurationAttribute::.ctor(string) = (
		01 00 05 44 65 62 75 67 00 00
	)
	.custom instance void [System.Runtime]System.Reflection.AssemblyFileVersionAttribute::.ctor(string) = (
		01 00 07 31 2e 30 2e 30 2e 30 00 00
	)
	.custom instance void [System.Runtime]System.Reflection.AssemblyInformationalVersionAttribute::.ctor(string) = (
		01 00 05 31 2e 30 2e 30 00 00
	)
	.custom instance void [System.Runtime]System.Reflection.AssemblyProductAttribute::.ctor(string) = (
		01 00 0b 54 61 73 6b 34 5f 4c 69 73 74 31 00 00
	)
	.custom instance void [System.Runtime]System.Reflection.AssemblyTitleAttribute::.ctor(string) = (
		01 00 0b 54 61 73 6b 34 5f 4c 69 73 74 31 00 00
	)
	.hash algorithm 0x00008004 // SHA1
	.ver 1:0:0:0
}

.module Task4_List1.dll
// MVID: {519251ED-BDD7-43D4-B557-872E6B0A1AC5}
.imagebase 0x00400000
.file alignment 0x00000200
.stackreserve 0x00100000
.subsystem 0x0003 // WindowsCui
.corflags 0x00000001 // ILOnly


.class private auto ansi '<Module>'
{
} // end of class <Module>

.class private auto ansi sealed beforefieldinit Microsoft.CodeAnalysis.EmbeddedAttribute
	extends [System.Runtime]System.Attribute
{
	.custom instance void [System.Runtime]System.Runtime.CompilerServices.CompilerGeneratedAttribute::.ctor() = (
		01 00 00 00
	)
	.custom instance void Microsoft.CodeAnalysis.EmbeddedAttribute::.ctor() = (
		01 00 00 00
	)
	// Methods
	.method public hidebysig specialname rtspecialname 
		instance void .ctor () cil managed 
	{
		// Method begins at RVA 0x2050
		// Header size: 1
		// Code size: 8 (0x8)
		.maxstack 8

		IL_0000: ldarg.0
		IL_0001: call instance void [System.Runtime]System.Attribute::.ctor()
		IL_0006: nop
		IL_0007: ret
	} // end of method EmbeddedAttribute::.ctor

} // end of class Microsoft.CodeAnalysis.EmbeddedAttribute

.class private auto ansi sealed beforefieldinit System.Runtime.CompilerServices.NullableAttribute
	extends [System.Runtime]System.Attribute
{
	.custom instance void [System.Runtime]System.Runtime.CompilerServices.CompilerGeneratedAttribute::.ctor() = (
		01 00 00 00
	)
	.custom instance void Microsoft.CodeAnalysis.EmbeddedAttribute::.ctor() = (
		01 00 00 00
	)
	.custom instance void [System.Runtime]System.AttributeUsageAttribute::.ctor(valuetype [System.Runtime]System.AttributeTargets) = (
		01 00 84 6b 00 00 02 00 54 02 0d 41 6c 6c 6f 77
		4d 75 6c 74 69 70 6c 65 00 54 02 09 49 6e 68 65
		72 69 74 65 64 00
	)
	// Fields
	.field public initonly uint8[] NullableFlags

	// Methods
	.method public hidebysig specialname rtspecialname 
		instance void .ctor (
			uint8 ''
		) cil managed 
	{
		// Method begins at RVA 0x2059
		// Header size: 1
		// Code size: 24 (0x18)
		.maxstack 8

		IL_0000: ldarg.0
		IL_0001: call instance void [System.Runtime]System.Attribute::.ctor()
		IL_0006: nop
		IL_0007: ldarg.0
		IL_0008: ldc.i4.1
		IL_0009: newarr [System.Runtime]System.Byte
		IL_000e: dup
		IL_000f: ldc.i4.0
		IL_0010: ldarg.1
		IL_0011: stelem.i1
		IL_0012: stfld uint8[] System.Runtime.CompilerServices.NullableAttribute::NullableFlags
		IL_0017: ret
	} // end of method NullableAttribute::.ctor

	.method public hidebysig specialname rtspecialname 
		instance void .ctor (
			uint8[] ''
		) cil managed 
	{
		// Method begins at RVA 0x2072
		// Header size: 1
		// Code size: 15 (0xf)
		.maxstack 8

		IL_0000: ldarg.0
		IL_0001: call instance void [System.Runtime]System.Attribute::.ctor()
		IL_0006: nop
		IL_0007: ldarg.0
		IL_0008: ldarg.1
		IL_0009: stfld uint8[] System.Runtime.CompilerServices.NullableAttribute::NullableFlags
		IL_000e: ret
	} // end of method NullableAttribute::.ctor

} // end of class System.Runtime.CompilerServices.NullableAttribute

.class private auto ansi sealed beforefieldinit System.Runtime.CompilerServices.NullableContextAttribute
	extends [System.Runtime]System.Attribute
{
	.custom instance void [System.Runtime]System.Runtime.CompilerServices.CompilerGeneratedAttribute::.ctor() = (
		01 00 00 00
	)
	.custom instance void Microsoft.CodeAnalysis.EmbeddedAttribute::.ctor() = (
		01 00 00 00
	)
	.custom instance void [System.Runtime]System.AttributeUsageAttribute::.ctor(valuetype [System.Runtime]System.AttributeTargets) = (
		01 00 4c 14 00 00 02 00 54 02 0d 41 6c 6c 6f 77
		4d 75 6c 74 69 70 6c 65 00 54 02 09 49 6e 68 65
		72 69 74 65 64 00
	)
	// Fields
	.field public initonly uint8 Flag

	// Methods
	.method public hidebysig specialname rtspecialname 
		instance void .ctor (
			uint8 ''
		) cil managed 
	{
		// Method begins at RVA 0x2082
		// Header size: 1
		// Code size: 15 (0xf)
		.maxstack 8

		IL_0000: ldarg.0
		IL_0001: call instance void [System.Runtime]System.Attribute::.ctor()
		IL_0006: nop
		IL_0007: ldarg.0
		IL_0008: ldarg.1
		IL_0009: stfld uint8 System.Runtime.CompilerServices.NullableContextAttribute::Flag
		IL_000e: ret
	} // end of method NullableContextAttribute::.ctor

} // end of class System.Runtime.CompilerServices.NullableContextAttribute

.class public auto ansi beforefieldinit Task1_List1.Example
	extends [System.Runtime]System.Object
{
	.custom instance void System.Runtime.CompilerServices.NullableContextAttribute::.ctor(uint8) = (
		01 00 01 00 00
	)
	.custom instance void System.Runtime.CompilerServices.NullableAttribute::.ctor(uint8) = (
		01 00 00 00 00
	)
	.custom instance void [System.Runtime]System.Reflection.DefaultMemberAttribute::.ctor(string) = (
		01 00 04 49 74 65 6d 00 00
	)
	// Fields
	.field private int32[] 'array'

	// Methods
	.method public hidebysig specialname rtspecialname 
		instance void .ctor () cil managed 
	{
		// Method begins at RVA 0x2092
		// Header size: 1
		// Code size: 25 (0x19)
		.maxstack 8

		IL_0000: ldarg.0
		IL_0001: call instance void [System.Runtime]System.Object::.ctor()
		IL_0006: nop
		IL_0007: nop
		IL_0008: ldarg.0
		IL_0009: ldc.i4.1
		IL_000a: newarr [System.Runtime]System.Int32
		IL_000f: dup
		IL_0010: ldc.i4.0
		IL_0011: ldc.i4.1
		IL_0012: stelem.i4
		IL_0013: stfld int32[] Task1_List1.Example::'array'
		IL_0018: ret
	} // end of method Example::.ctor

	.method public hidebysig specialname rtspecialname 
		instance void .ctor (
			int32[] input
		) cil managed 
	{
		.param [1]
			.custom instance void [System.Runtime]System.ParamArrayAttribute::.ctor() = (
				01 00 00 00
			)
		// Method begins at RVA 0x20ac
		// Header size: 12
		// Code size: 52 (0x34)
		.maxstack 4
		.locals init (
			[0] int32 i,
			[1] bool
		)

		IL_0000: ldarg.0
		IL_0001: call instance void [System.Runtime]System.Object::.ctor()
		IL_0006: nop
		IL_0007: nop
		IL_0008: ldarg.0
		IL_0009: ldarg.1
		IL_000a: ldlen
		IL_000b: conv.i4
		IL_000c: newarr [System.Runtime]System.Int32
		IL_0011: stfld int32[] Task1_List1.Example::'array'
		IL_0016: ldc.i4.0
		IL_0017: stloc.0
		IL_0018: br.s IL_0029
		// loop start (head: IL_0029)
			IL_001a: ldarg.0
			IL_001b: ldfld int32[] Task1_List1.Example::'array'
			IL_0020: ldloc.0
			IL_0021: ldarg.1
			IL_0022: ldloc.0
			IL_0023: ldelem.i4
			IL_0024: stelem.i4
			IL_0025: ldloc.0
			IL_0026: ldc.i4.1
			IL_0027: add
			IL_0028: stloc.0

			IL_0029: ldloc.0
			IL_002a: ldarg.1
			IL_002b: ldlen
			IL_002c: conv.i4
			IL_002d: clt
			IL_002f: stloc.1
			IL_0030: ldloc.1
			IL_0031: brtrue.s IL_001a
		// end loop

		IL_0033: ret
	} // end of method Example::.ctor

	.method public hidebysig 
		instance void printArray () cil managed 
	{
		// Method begins at RVA 0x20ec
		// Header size: 12
		// Code size: 41 (0x29)
		.maxstack 2
		.locals init (
			[0] int32 i,
			[1] bool
		)

		IL_0000: nop
		IL_0001: ldc.i4.0
		IL_0002: stloc.0
		IL_0003: br.s IL_0019
		// loop start (head: IL_0019)
			IL_0005: nop
			IL_0006: ldarg.0
			IL_0007: ldfld int32[] Task1_List1.Example::'array'
			IL_000c: ldloc.0
			IL_000d: ldelem.i4
			IL_000e: call void [System.Console]System.Console::WriteLine(int32)
			IL_0013: nop
			IL_0014: nop
			IL_0015: ldloc.0
			IL_0016: ldc.i4.1
			IL_0017: add
			IL_0018: stloc.0

			IL_0019: ldloc.0
			IL_001a: ldarg.0
			IL_001b: ldfld int32[] Task1_List1.Example::'array'
			IL_0020: ldlen
			IL_0021: conv.i4
			IL_0022: clt
			IL_0024: stloc.1
			IL_0025: ldloc.1
			IL_0026: brtrue.s IL_0005
		// end loop

		IL_0028: ret
	} // end of method Example::printArray

	.method public hidebysig specialname 
		instance int32 get_Item (
			int32 i
		) cil managed 
	{
		// Method begins at RVA 0x2124
		// Header size: 12
		// Code size: 14 (0xe)
		.maxstack 2
		.locals init (
			[0] int32
		)

		IL_0000: nop
		IL_0001: ldarg.0
		IL_0002: ldfld int32[] Task1_List1.Example::'array'
		IL_0007: ldarg.1
		IL_0008: ldelem.i4
		IL_0009: stloc.0
		IL_000a: br.s IL_000c

		IL_000c: ldloc.0
		IL_000d: ret
	} // end of method Example::get_Item

	.method public hidebysig specialname 
		instance void set_Item (
			int32 i,
			int32 'value'
		) cil managed 
	{
		// Method begins at RVA 0x213e
		// Header size: 1
		// Code size: 11 (0xb)
		.maxstack 8

		IL_0000: nop
		IL_0001: ldarg.0
		IL_0002: ldfld int32[] Task1_List1.Example::'array'
		IL_0007: ldarg.1
		IL_0008: ldarg.2
		IL_0009: stelem.i4
		IL_000a: ret
	} // end of method Example::set_Item

	.method public hidebysig specialname 
		instance int32 get_numberOfElements () cil managed 
	{
		// Method begins at RVA 0x214c
		// Header size: 12
		// Code size: 14 (0xe)
		.maxstack 1
		.locals init (
			[0] int32
		)

		IL_0000: nop
		IL_0001: ldarg.0
		IL_0002: ldfld int32[] Task1_List1.Example::'array'
		IL_0007: ldlen
		IL_0008: conv.i4
		IL_0009: stloc.0
		IL_000a: br.s IL_000c

		IL_000c: ldloc.0
		IL_000d: ret
	} // end of method Example::get_numberOfElements

	// Properties
	.property instance int32 Item(
		int32 i
	)
	{
		.get instance int32 Task1_List1.Example::get_Item(int32)
		.set instance void Task1_List1.Example::set_Item(int32, int32)
	}
	.property instance int32 numberOfElements()
	{
		.get instance int32 Task1_List1.Example::get_numberOfElements()
	}

} // end of class Task1_List1.Example

.class public auto ansi sealed Task1_List1.PerformCalculation
	extends [System.Runtime]System.MulticastDelegate
{
	// Methods
	.method public hidebysig specialname rtspecialname 
		instance void .ctor (
			object 'object',
			native int 'method'
		) runtime managed 
	{
	} // end of method PerformCalculation::.ctor

	.method public hidebysig newslot virtual 
		instance void Invoke (
			int32 x,
			int32 y
		) runtime managed 
	{
	} // end of method PerformCalculation::Invoke

	.method public hidebysig newslot virtual 
		instance class [System.Runtime]System.IAsyncResult BeginInvoke (
			int32 x,
			int32 y,
			class [System.Runtime]System.AsyncCallback callback,
			object 'object'
		) runtime managed 
	{
	} // end of method PerformCalculation::BeginInvoke

	.method public hidebysig newslot virtual 
		instance void EndInvoke (
			class [System.Runtime]System.IAsyncResult result
		) runtime managed 
	{
	} // end of method PerformCalculation::EndInvoke

} // end of class Task1_List1.PerformCalculation

.class public auto ansi beforefieldinit Task1_List1.Calculation
	extends [System.Runtime]System.Object
{
	// Methods
	.method public hidebysig 
		instance void printAdd (
			int32 x,
			int32 y
		) cil managed 
	{
		// Method begins at RVA 0x2166
		// Header size: 1
		// Code size: 11 (0xb)
		.maxstack 8

		IL_0000: nop
		IL_0001: ldarg.1
		IL_0002: ldarg.2
		IL_0003: add
		IL_0004: call void [System.Console]System.Console::WriteLine(int32)
		IL_0009: nop
		IL_000a: ret
	} // end of method Calculation::printAdd

	.method public hidebysig 
		instance void printSub (
			int32 x,
			int32 y
		) cil managed 
	{
		// Method begins at RVA 0x2172
		// Header size: 1
		// Code size: 11 (0xb)
		.maxstack 8

		IL_0000: nop
		IL_0001: ldarg.1
		IL_0002: ldarg.2
		IL_0003: sub
		IL_0004: call void [System.Console]System.Console::WriteLine(int32)
		IL_0009: nop
		IL_000a: ret
	} // end of method Calculation::printSub

	.method public hidebysig specialname rtspecialname 
		instance void .ctor () cil managed 
	{
		// Method begins at RVA 0x217e
		// Header size: 1
		// Code size: 8 (0x8)
		.maxstack 8

		IL_0000: ldarg.0
		IL_0001: call instance void [System.Runtime]System.Object::.ctor()
		IL_0006: nop
		IL_0007: ret
	} // end of method Calculation::.ctor

} // end of class Task1_List1.Calculation

.class public auto ansi sealed Task1_List1.Notify
	extends [System.Runtime]System.MulticastDelegate
{
	// Methods
	.method public hidebysig specialname rtspecialname 
		instance void .ctor (
			object 'object',
			native int 'method'
		) runtime managed 
	{
	} // end of method Notify::.ctor

	.method public hidebysig newslot virtual 
		instance void Invoke () runtime managed 
	{
	} // end of method Notify::Invoke

	.method public hidebysig newslot virtual 
		instance class [System.Runtime]System.IAsyncResult BeginInvoke (
			class [System.Runtime]System.AsyncCallback callback,
			object 'object'
		) runtime managed 
	{
	} // end of method Notify::BeginInvoke

	.method public hidebysig newslot virtual 
		instance void EndInvoke (
			class [System.Runtime]System.IAsyncResult result
		) runtime managed 
	{
	} // end of method Notify::EndInvoke

} // end of class Task1_List1.Notify

.class public auto ansi beforefieldinit Task1_List1.EventExample
	extends [System.Runtime]System.Object
{
	.custom instance void System.Runtime.CompilerServices.NullableContextAttribute::.ctor(uint8) = (
		01 00 01 00 00
	)
	.custom instance void System.Runtime.CompilerServices.NullableAttribute::.ctor(uint8) = (
		01 00 00 00 00
	)
	// Fields
	.field private class Task1_List1.Notify ProcessCompleted
	.custom instance void [System.Runtime]System.Runtime.CompilerServices.CompilerGeneratedAttribute::.ctor() = (
		01 00 00 00
	)
	.custom instance void [System.Runtime]System.Diagnostics.DebuggerBrowsableAttribute::.ctor(valuetype [System.Runtime]System.Diagnostics.DebuggerBrowsableState) = (
		01 00 00 00 00 00 00 00
	)

	// Methods
	.method public hidebysig specialname 
		instance void add_ProcessCompleted (
			class Task1_List1.Notify 'value'
		) cil managed 
	{
		.custom instance void [System.Runtime]System.Runtime.CompilerServices.CompilerGeneratedAttribute::.ctor() = (
			01 00 00 00
		)
		// Method begins at RVA 0x2188
		// Header size: 12
		// Code size: 41 (0x29)
		.maxstack 3
		.locals init (
			[0] class Task1_List1.Notify,
			[1] class Task1_List1.Notify,
			[2] class Task1_List1.Notify
		)

		IL_0000: ldarg.0
		IL_0001: ldfld class Task1_List1.Notify Task1_List1.EventExample::ProcessCompleted
		IL_0006: stloc.0
		// loop start (head: IL_0007)
			IL_0007: ldloc.0
			IL_0008: stloc.1
			IL_0009: ldloc.1
			IL_000a: ldarg.1
			IL_000b: call class [System.Runtime]System.Delegate [System.Runtime]System.Delegate::Combine(class [System.Runtime]System.Delegate, class [System.Runtime]System.Delegate)
			IL_0010: castclass Task1_List1.Notify
			IL_0015: stloc.2
			IL_0016: ldarg.0
			IL_0017: ldflda class Task1_List1.Notify Task1_List1.EventExample::ProcessCompleted
			IL_001c: ldloc.2
			IL_001d: ldloc.1
			IL_001e: call !!0 [System.Threading]System.Threading.Interlocked::CompareExchange<class Task1_List1.Notify>(!!0&, !!0, !!0)
			IL_0023: stloc.0
			IL_0024: ldloc.0
			IL_0025: ldloc.1
			IL_0026: bne.un.s IL_0007
		// end loop
		IL_0028: ret
	} // end of method EventExample::add_ProcessCompleted

	.method public hidebysig specialname 
		instance void remove_ProcessCompleted (
			class Task1_List1.Notify 'value'
		) cil managed 
	{
		.custom instance void [System.Runtime]System.Runtime.CompilerServices.CompilerGeneratedAttribute::.ctor() = (
			01 00 00 00
		)
		// Method begins at RVA 0x21c0
		// Header size: 12
		// Code size: 41 (0x29)
		.maxstack 3
		.locals init (
			[0] class Task1_List1.Notify,
			[1] class Task1_List1.Notify,
			[2] class Task1_List1.Notify
		)

		IL_0000: ldarg.0
		IL_0001: ldfld class Task1_List1.Notify Task1_List1.EventExample::ProcessCompleted
		IL_0006: stloc.0
		// loop start (head: IL_0007)
			IL_0007: ldloc.0
			IL_0008: stloc.1
			IL_0009: ldloc.1
			IL_000a: ldarg.1
			IL_000b: call class [System.Runtime]System.Delegate [System.Runtime]System.Delegate::Remove(class [System.Runtime]System.Delegate, class [System.Runtime]System.Delegate)
			IL_0010: castclass Task1_List1.Notify
			IL_0015: stloc.2
			IL_0016: ldarg.0
			IL_0017: ldflda class Task1_List1.Notify Task1_List1.EventExample::ProcessCompleted
			IL_001c: ldloc.2
			IL_001d: ldloc.1
			IL_001e: call !!0 [System.Threading]System.Threading.Interlocked::CompareExchange<class Task1_List1.Notify>(!!0&, !!0, !!0)
			IL_0023: stloc.0
			IL_0024: ldloc.0
			IL_0025: ldloc.1
			IL_0026: bne.un.s IL_0007
		// end loop
		IL_0028: ret
	} // end of method EventExample::remove_ProcessCompleted

	.method public hidebysig 
		instance void StartProcess () cil managed 
	{
		// Method begins at RVA 0x21f5
		// Header size: 1
		// Code size: 20 (0x14)
		.maxstack 8

		IL_0000: nop
		IL_0001: ldstr "Process Started!"
		IL_0006: call void [System.Console]System.Console::WriteLine(string)
		IL_000b: nop
		IL_000c: ldarg.0
		IL_000d: callvirt instance void Task1_List1.EventExample::OnProcessCompleted()
		IL_0012: nop
		IL_0013: ret
	} // end of method EventExample::StartProcess

	.method family hidebysig newslot virtual 
		instance void OnProcessCompleted () cil managed 
	{
		// Method begins at RVA 0x220a
		// Header size: 1
		// Code size: 31 (0x1f)
		.maxstack 8

		IL_0000: nop
		IL_0001: ldstr "Process Completed!"
		IL_0006: call void [System.Console]System.Console::WriteLine(string)
		IL_000b: nop
		IL_000c: ldarg.0
		IL_000d: ldfld class Task1_List1.Notify Task1_List1.EventExample::ProcessCompleted
		IL_0012: dup
		IL_0013: brtrue.s IL_0018

		IL_0015: pop
		IL_0016: br.s IL_001e

		IL_0018: callvirt instance void Task1_List1.Notify::Invoke()
		IL_001d: nop

		IL_001e: ret
	} // end of method EventExample::OnProcessCompleted

	.method public hidebysig specialname rtspecialname 
		instance void .ctor () cil managed 
	{
		// Method begins at RVA 0x222a
		// Header size: 1
		// Code size: 8 (0x8)
		.maxstack 8

		IL_0000: ldarg.0
		IL_0001: call instance void [System.Runtime]System.Object::.ctor()
		IL_0006: nop
		IL_0007: ret
	} // end of method EventExample::.ctor

	// Events
	.event Task1_List1.Notify ProcessCompleted
	{
		.addon instance void Task1_List1.EventExample::add_ProcessCompleted(class Task1_List1.Notify)
		.removeon instance void Task1_List1.EventExample::remove_ProcessCompleted(class Task1_List1.Notify)
	}


} // end of class Task1_List1.EventExample

.class private auto ansi beforefieldinit Task1_List1.Program
	extends [System.Runtime]System.Object
{
	// Methods
	.method private hidebysig static 
		void Main () cil managed 
	{
		// Method begins at RVA 0x2234
		// Header size: 12
		// Code size: 339 (0x153)
		.maxstack 3
		.entrypoint
		.locals init (
			[0] class Task1_List1.Calculation calculation,
			[1] class Task1_List1.PerformCalculation perform,
			[2] class Task1_List1.EventExample new_event,
			[3] class Task1_List1.Example example,
			[4] class Task1_List1.Example example2,
			[5] bool t,
			[6] bool f,
			[7] int32 caseSwitch,
			[8] int32 i,
			[9] bool,
			[10] bool,
			[11] bool,
			[12] int32,
			[13] int32
		)

		IL_0000: nop
		IL_0001: newobj instance void Task1_List1.Calculation::.ctor()
		IL_0006: stloc.0
		IL_0007: ldloc.0
		IL_0008: ldftn instance void Task1_List1.Calculation::printAdd(int32, int32)
		IL_000e: newobj instance void Task1_List1.PerformCalculation::.ctor(object, native int)
		IL_0013: stloc.1
		IL_0014: ldstr "Calling the delegate:"
		IL_0019: call void [System.Console]System.Console::WriteLine(string)
		IL_001e: nop
		IL_001f: ldloc.1
		IL_0020: ldc.i4.5
		IL_0021: ldc.i4.5
		IL_0022: callvirt instance void Task1_List1.PerformCalculation::Invoke(int32, int32)
		IL_0027: nop
		IL_0028: ldstr "Event example:"
		IL_002d: call void [System.Console]System.Console::WriteLine(string)
		IL_0032: nop
		IL_0033: newobj instance void Task1_List1.EventExample::.ctor()
		IL_0038: stloc.2
		IL_0039: ldloc.2
		IL_003a: callvirt instance void Task1_List1.EventExample::StartProcess()
		IL_003f: nop
		IL_0040: ldstr "Example class with indexer:"
		IL_0045: call void [System.Console]System.Console::WriteLine(string)
		IL_004a: nop
		IL_004b: ldc.i4.3
		IL_004c: newarr [System.Runtime]System.Int32
		IL_0051: dup
		IL_0052: ldtoken field valuetype '<PrivateImplementationDetails>'/'__StaticArrayInitTypeSize=12' '<PrivateImplementationDetails>'::'4636993D3E1DA4E9D6B8F87B79E8F7C6D018580D52661950EABC3845C5897A4D'
		IL_0057: call void [System.Runtime]System.Runtime.CompilerServices.RuntimeHelpers::InitializeArray(class [System.Runtime]System.Array, valuetype [System.Runtime]System.RuntimeFieldHandle)
		IL_005c: newobj instance void Task1_List1.Example::.ctor(int32[])
		IL_0061: stloc.3
		IL_0062: newobj instance void Task1_List1.Example::.ctor()
		IL_0067: stloc.s 4
		IL_0069: ldloc.3
		IL_006a: ldc.i4.0
		IL_006b: ldc.i4.4
		IL_006c: callvirt instance void Task1_List1.Example::set_Item(int32, int32)
		IL_0071: nop
		IL_0072: ldloc.3
		IL_0073: ldc.i4.1
		IL_0074: ldc.i4.5
		IL_0075: callvirt instance void Task1_List1.Example::set_Item(int32, int32)
		IL_007a: nop
		IL_007b: ldc.i4.0
		IL_007c: stloc.s 8
		IL_007e: br.s IL_0096
		// loop start (head: IL_0096)
			IL_0080: nop
			IL_0081: ldloc.3
			IL_0082: ldloc.s 8
			IL_0084: callvirt instance int32 Task1_List1.Example::get_Item(int32)
			IL_0089: call void [System.Console]System.Console::WriteLine(int32)
			IL_008e: nop
			IL_008f: nop
			IL_0090: ldloc.s 8
			IL_0092: ldc.i4.1
			IL_0093: add
			IL_0094: stloc.s 8

			IL_0096: ldloc.s 8
			IL_0098: ldloc.3
			IL_0099: callvirt instance int32 Task1_List1.Example::get_numberOfElements()
			IL_009e: clt
			IL_00a0: stloc.s 9
			IL_00a2: ldloc.s 9
			IL_00a4: brtrue.s IL_0080
		// end loop

		IL_00a6: ldstr "If with boolean variables:"
		IL_00ab: call void [System.Console]System.Console::WriteLine(string)
		IL_00b0: nop
		IL_00b1: ldc.i4.1
		IL_00b2: stloc.s 5
		IL_00b4: ldc.i4.0
		IL_00b5: stloc.s 6
		IL_00b7: ldloc.s 5
		IL_00b9: stloc.s 10
		IL_00bb: ldloc.s 10
		IL_00bd: brfalse.s IL_00c9

		IL_00bf: ldloc.s 5
		IL_00c1: call void [System.Console]System.Console::WriteLine(bool)
		IL_00c6: nop
		IL_00c7: br.s IL_00d1

		IL_00c9: ldloc.s 6
		IL_00cb: call void [System.Console]System.Console::WriteLine(bool)
		IL_00d0: nop

		IL_00d1: ldloc.s 6
		IL_00d3: stloc.s 11
		IL_00d5: ldloc.s 11
		IL_00d7: brfalse.s IL_00e3

		IL_00d9: ldloc.s 5
		IL_00db: call void [System.Console]System.Console::WriteLine(bool)
		IL_00e0: nop
		IL_00e1: br.s IL_00eb

		IL_00e3: ldloc.s 6
		IL_00e5: call void [System.Console]System.Console::WriteLine(bool)
		IL_00ea: nop

		IL_00eb: ldstr "Switch case:"
		IL_00f0: call void [System.Console]System.Console::WriteLine(string)
		IL_00f5: nop
		IL_00f6: ldc.i4.5
		IL_00f7: stloc.s 7
		IL_00f9: ldloc.s 7
		IL_00fb: stloc.s 13
		IL_00fd: ldloc.s 13
		IL_00ff: stloc.s 12
		IL_0101: ldloc.s 12
		IL_0103: ldc.i4.1
		IL_0104: sub
		IL_0105: switch (IL_0118, IL_0125, IL_0132)

		IL_0116: br.s IL_013f

		IL_0118: ldstr "Case 1"
		IL_011d: call void [System.Console]System.Console::WriteLine(string)
		IL_0122: nop
		IL_0123: br.s IL_014c

		IL_0125: ldstr "Case 2"
		IL_012a: call void [System.Console]System.Console::WriteLine(string)
		IL_012f: nop
		IL_0130: br.s IL_014c

		IL_0132: ldstr "Case 3"
		IL_0137: call void [System.Console]System.Console::WriteLine(string)
		IL_013c: nop
		IL_013d: br.s IL_014c

		IL_013f: ldstr "Case default"
		IL_0144: call void [System.Console]System.Console::WriteLine(string)
		IL_0149: nop
		IL_014a: br.s IL_014c

		IL_014c: call string [System.Console]System.Console::ReadLine()
		IL_0151: pop
		IL_0152: ret
	} // end of method Program::Main

	.method public hidebysig specialname rtspecialname 
		instance void .ctor () cil managed 
	{
		// Method begins at RVA 0x2393
		// Header size: 1
		// Code size: 8 (0x8)
		.maxstack 8

		IL_0000: ldarg.0
		IL_0001: call instance void [System.Runtime]System.Object::.ctor()
		IL_0006: nop
		IL_0007: ret
	} // end of method Program::.ctor

} // end of class Task1_List1.Program

.class private auto ansi sealed '<PrivateImplementationDetails>'
	extends [System.Runtime]System.Object
{
	.custom instance void [System.Runtime]System.Runtime.CompilerServices.CompilerGeneratedAttribute::.ctor() = (
		01 00 00 00
	)
	// Nested Types
	.class nested private explicit ansi sealed '__StaticArrayInitTypeSize=12'
		extends [System.Runtime]System.ValueType
	{
		.pack 1
		.size 12

	} // end of class __StaticArrayInitTypeSize=12


	// Fields
	.field assembly static initonly valuetype '<PrivateImplementationDetails>'/'__StaticArrayInitTypeSize=12' '4636993D3E1DA4E9D6B8F87B79E8F7C6D018580D52661950EABC3845C5897A4D' at I_00003400
	.data cil I_00003400 = bytearray (
		01 00 00 00 02 00 00 00 03 00 00 00
	)

} // end of class <PrivateImplementationDetails>

