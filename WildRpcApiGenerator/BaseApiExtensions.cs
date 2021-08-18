using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

namespace WildRpcApiGenerator
{
	/// <summary>
	/// Manually-edited part of the BaseApiGenerator template.
	/// </summary>
	public abstract partial class BaseApiGenerator
	{
		public string outputDir;
		public ReflectionDb reflectionDb;

		protected bool isEnum(ReflectionMethod.Parameter param)
		{
			return isEnum(param.elementTypeName);
		}
		protected bool isEnum(string type)
		{
			return reflectionDb.enums.Any(e => e.name == type);
		}
	}

	public class ReflectionProperty
	{
		public string name;
		public ReflectionMethod getter;
		public ReflectionMethod setter;
	}

	public static class ApiGeneratorExtensions
	{
		public static string niceName(this string name)
		{
			return name.Replace("RPC_", "");
		}
		public static string niceName(this ReflectionMethod method)
		{
			return niceName(method.name);
		}

		public static List<ReflectionProperty> findProperties(this ReflectionClass cls)
		{
			var properties = new List<ReflectionProperty>();

			foreach (var getter in cls.methods)
			{
				var setterName = getter.name.Replace("_Get", "_Set");
				if (setterName == getter.name)
				{
					continue; // not a getter
				}

				var setter = cls.methods.FirstOrDefault(m => m.name == setterName);
				if (setter == null)
				{
					continue; // no setter
				}

				// TODO check types match

				properties.Add(new ReflectionProperty
				{
					name = niceName(getter.name.Replace("_Get", "_")),
					getter = getter,
					setter = setter,
				});
			}

			return properties;
		}

		public static string join(this IEnumerable<string> strings, Func<string, string> converter = null)
		{
			return string.Join(", ", converter != null ? strings.Select(converter) : strings);
		}
		public static string join(this IEnumerable<ReflectionMethod.Parameter> @params, Func<ReflectionMethod.Parameter, string> converter = null)
		{
			return string.Join(", ", @params.Select(converter));
		}
		public static string joinNames(this ReflectionMethod.Parameter[] @params, Func<string, string> converter = null)
		{
			return join(@params.Select(p => p.name), converter);
		}
	}
}
