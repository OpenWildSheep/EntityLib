using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.Json;

namespace WildRpcApiGenerator
{
	public enum ContainerType : short
	{
		Invalid = -1,
		Scalar = 0,
		Array = 1,
	}

	public enum ElementType : short
	{
		Invalid = -1,
		Boolean = 0,
		Integer = 1,
		Float = 2,
		Vector2 = 3,
		UInt3 = 4,
		Vector3 = 5,
		Quat = 6,
		Color = 7,
		Position = 8,
		String = 9,
	}

	public class ReflectionMethod
	{
		public class Parameter
		{
			public string name;
			public string typeName; // for debug
			public ContainerType containerType;
			public bool isArray => containerType != ContainerType.Scalar; // HACK: use "!= Scalar" instead of "== Array" for "RPC_UnsupportedType" test case
			public ElementType elementType;
			public string elementTypeName; // for eg enums
			public bool isValid => containerType != ContainerType.Invalid && elementType != ElementType.Invalid;
		}

		public string name;
		public bool threadSafe;
		public Parameter[] inputs;
		public Parameter[] outputs;

		public IEnumerable<Parameter> parameters => inputs.Concat(outputs);
		public bool isValid => parameters.All(i => i.isValid);
	}

	public class ReflectionClass
	{
		public string name;
		public ReflectionMethod[] methods;
		public IEnumerable<ReflectionMethod> validMethods => methods.Where(m => m.isValid);
	}

	public class ReflectionEnum
	{
		public string name;
		public int[] values;
		public string[] names;
	}

	public class ReflectionDb
	{
		public ReflectionClass[] classes;
		public ReflectionEnum[] enums;
	}


	class Program
	{
		const string inputSchema = @"X:\Tools\WildPipeline\Schema\wild_rpc_api.json";
		static readonly BaseApiGenerator[] generators =
		{
			new PythonApiGenerator {outputDir = @"D:\WildCode\WildScripts\WildDcc\wild\core\rpc_api\wild_api.py"},
			new MaxApiGenerator {outputDir = @"D:\WildCode\WildScripts\WildMaxCpp\RpcApiWild.h"},
		};

		static void Main(string[] args)
		{
			string json = File.ReadAllText(inputSchema);
			var db = JsonSerializer.Deserialize<ReflectionDb>(json, new JsonSerializerOptions { IncludeFields = true });
			//db.classes = Array.FindAll(db.classes, c => c.name != "TestMethodMarshalling");
			Array.Sort(db.classes, (a, b) => string.CompareOrdinal(a.name, b.name));
			Array.Sort(db.enums, (a, b) => string.CompareOrdinal(a.name, b.name));

			foreach (var generator in generators)
			{
				generator.reflectionDb = db;
				var output = generator.TransformText();
				File.WriteAllText(generator.outputDir, output);
			}
		}
	}


	public static class StringExtensions
	{
		public static string ToLowerFirstLetter(this string str)
		{
			if (string.IsNullOrWhiteSpace(str))
			{
				return str;
			}

			var chars = str.ToCharArray();
			chars[0] = char.ToLower(chars[0]);
			return new string(chars);
		}

		public static string ToUpperFirstLetter(this string str)
		{
			if (string.IsNullOrWhiteSpace(str))
			{
				return str;
			}

			var chars = str.ToCharArray();
			chars[0] = char.ToUpper(chars[0]);
			return new string(chars);
		}
	}

	public static class ArrayExtensions
	{
		public static void Add<T>(ref T[] array, T item)
		{
			Array.Resize(ref array, array.Length + 1);
			array[^1] = item;
		}

		public static IEnumerable<(int index, T item)> Enumerate<T>(this IEnumerable<T> _this)
		{
			int i = 0;
			foreach (var item in _this)
			{
				yield return (i++, item);
			}
		}
	}
}
