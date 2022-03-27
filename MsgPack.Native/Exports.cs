using MessagePack;
using RGiesecke.DllExport;
using System;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace MsgPack.Native
{
	public class Exports
	{
		private const uint E_InvalidArg = 0x80070057;
		private const uint S_OK = 0;


		[DllExport(CallingConvention = CallingConvention.StdCall)]
		[return: MarshalAs(UnmanagedType.BStr)]
		public static string ConvertToJson(IntPtr pBytes, int cBytes)
		{
			byte[] data = new byte[cBytes];
			Marshal.Copy(pBytes, data, 0, cBytes);
			string result = MessagePackSerializer.ConvertToJson(data);
			return result;
		}

		[DllExport(CallingConvention = CallingConvention.StdCall)]
		public static uint ConvertToJsonBuf(IntPtr pBytes, int cBytes, IntPtr pOutBytes, ref IntPtr cOutBytes)
		{
			byte[] data = new byte[cBytes];
			Marshal.Copy(pBytes, data, 0, cBytes);
			string result = MessagePackSerializer.ConvertToJson(data);
			byte[] outBytes = Encoding.UTF8.GetBytes(result);
			if (outBytes.Length > (int)cOutBytes)
			{
				cOutBytes = (IntPtr)outBytes.Length;
				return E_InvalidArg;
			}
			cOutBytes = (IntPtr)outBytes.Length;
			Marshal.Copy(outBytes, 0, pOutBytes, outBytes.Length);
			return S_OK;
		}

#if DEBUG
		[DllExport(CallingConvention = CallingConvention.StdCall)]
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
