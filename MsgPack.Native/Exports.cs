using MessagePack;
using RGiesecke.DllExport;
using System;
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
	}
}
