#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Dictionary/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Test_Dictionary_getSize)
		{
			Dict<int, int> dic;
			Assert::AreEqual(0, dic.getsize());
		}

		TEST_METHOD(Test_Dictionary_add)
		{
			Dict<int, int> dic;
			dic.add(5, 10);
			Assert::AreEqual(1, dic.getsize());
		}

		TEST_METHOD(Test_Dictionary_find)
		{
			Dict<char, int> dic;
			dic.add('A', 10);
			int a;
			dic.find('A', a);
			Assert::AreEqual(10, a);
		}

		TEST_METHOD(Test_Dictionary_erase)
		{
			Dict<int, int> dic;
			dic.add(5, 10);
			dic.erase(5);
			Assert::AreEqual(0, dic.getsize());
		}
		
	};
}