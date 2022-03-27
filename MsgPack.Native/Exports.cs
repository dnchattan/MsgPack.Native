using MessagePack;
using RGiesecke.DllExport;
using System;
using System.Linq;
using System.Runtime.InteropServices;

namespace MsgPack.Native
{
	public class Exports
	{
		[DllExport(CallingConvention = CallingConvention.Winapi)]
		[return: MarshalAs(UnmanagedType.BStr)]
		public static string ConvertToJson(IntPtr pBytes, int cBytes)
		{
			byte[] data = new byte[cBytes];
			Marshal.Copy(pBytes, data, 0, cBytes);
			string result = MessagePackSerializer.ConvertToJson(data);
			return result;
		}

#if DEBUG
		[DllExport(CallingConvention = CallingConvention.Winapi)]
		[return: MarshalAs(UnmanagedType.BStr)]
		public static string ConvertToJson_DEBUG(IntPtr pBytes, int cBytes)
		{
			byte[] data = new byte[cBytes];
			Marshal.Copy(pBytes, data, 0, cBytes);
			Console.WriteLine("Input[0-500]: ");
			Console.WriteLine(string.Join(",", data.Take(100)));
			string result = MessagePackSerializer.ConvertToJson(data);
			Console.WriteLine("Output[0-500]: ");
			Console.WriteLine(result.Substring(0, 500));
			return result;
		}
#endif
	}
}
