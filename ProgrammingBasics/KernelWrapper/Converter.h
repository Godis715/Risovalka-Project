#pragma once
#include <string>
#include "Array.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Helpers {
	public class Converter
	{
	public:

		static std::string ToStdString(String^ str)
		{
			// NOT RELIABLE: it can be memory lick there
			char* charArr = (char*)Marshal::StringToHGlobalAnsi(str).ToPointer();
			return std::string(charArr);
		}

		template<typename T>
		static DrawProject::Array<T> ToDrawProjArray(array<T>^ arr)
		{
			auto newArr = DrawProject::Array<T>(arr->Length);
			for (int i = 0; i < arr->Length; ++i)
			{
				newArr[i] = arr[i];
			}
			return newArr;
		}

		template<typename T>
		static array<T>^ ToDotNetArray(const DrawProject::Array<T>& arr)
		{
			auto newArr = gcnew array<T>(arr.GetSize());
			for (int i = 0; i < arr.GetSize(); ++i)
			{
				newArr[i] = arr[i];
			}
			return newArr;
		}

		static array<String^>^ ToDotNetArrayStr(const DrawProject::Array<std::string>& arr)
		{
			auto newArr = gcnew array<String^>(arr.GetSize());
			for (int i = 0; i < arr.GetSize(); ++i)
			{
				newArr[i] = gcnew String(arr[i].c_str());
			}
			return newArr;
		}
	};
}
