#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Array/Array.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ArrayTests
{		
	TEST_CLASS(BasicFunctionality)
	{
	public:
		
		TEST_METHOD(Test_Array_Construcor_getSize)
		{
			Array<int> arr;
			Assert::AreEqual(0, arr.getSize());
			Array<double> arr1 = Array<double>(10);
			Assert::AreEqual(10, arr1.getSize());
		}

		TEST_METHOD(Test_Array_pushBack)
		{
			Array<double> arr;
			arr.pushBack(3.14);
			Assert::AreEqual(1, arr.getSize());
		}

		TEST_METHOD(Test_Array_pushBack_overflow)
		{
			Array<int> arr;
			for (int i = 0; i < 512; i++)
			{
				arr.pushBack(i);
			}
			arr.pushBack(512);
			Assert::AreEqual(513, arr.getSize());
		}

		TEST_METHOD(Test_Array_popBack)
		{
			Array<int> arr;
			arr.pushBack(1);
			Assert::AreEqual(1, arr.popBack());
		}

		TEST_METHOD(Test_Array_isEmpty)
		{
			Array<int> arr;
			Assert::AreEqual(true, arr.isEmpty());
		}

		TEST_METHOD(Test_Array_resize_DeleteAllValues)
		{
			Array<int> arr;
			arr.resize(0);
			Assert::AreEqual(true, arr.isEmpty());
			for (int i = 0; i < 10; i++)
			{
				arr.pushBack(i);
			}
			arr.resize(0);
			Assert::AreEqual(true, arr.isEmpty());
		}

		TEST_METHOD(Test_Array_resize_Deleting)
		{
			Array<int> arr;
			for (int i = 0; i < 10; i++)
			{
				arr.pushBack(i);
			}
			arr.resize(5);
			
			bool exceptionIsCatched = false;
			try
			{
				int a = arr[5];
			}
			catch (std::out_of_range)
			{
				exceptionIsCatched = true;
			}
			Assert::AreEqual(true, exceptionIsCatched);
		}

		TEST_METHOD(Test_Array_resize_FillingDefault)
		{
			Array<int> arr;
			for (int i = 0; i < 10; i++)
			{
				arr.pushBack(i);
			}
			arr.resize(15);
			for (int i = 0; i < 15; i++)
			{
				if (i < 10)
				{
					Assert::AreEqual(i, arr[i]);
				}
				else Assert::AreEqual(0, arr[i]);
			}
		}

		TEST_METHOD(Test_Array_clear)
		{
			Array<int> arr;
			for (int i = 0; i < 10; i++)
			{
				arr.pushBack(i);
			}
			arr.clear();
			Assert::AreEqual(true, arr.isEmpty());
		}

		TEST_METHOD(Test_Array_swap)
		{
			Array<int> arr;
			for (int i = 0; i < 10; i++)
			{
				arr.pushBack(i);
			}
			arr.swap(0, 9);
			Assert::AreEqual(0, arr[9]);
			Assert::AreEqual(9, arr[0]);
		}

		TEST_METHOD(Test_Array_sort)
		{
			Array<int> arr;
			for (int i = 0; i < 10; i++)
			{
				arr.pushBack(i);
			}
			arr.sort(0, 9);
			bool isSorted = true;
			for (int i = 1; i < 10; i++)
			{
				if (arr[i] < arr[i - 1])
				{
					isSorted = false;
				}
			}
			Assert::AreEqual(true, isSorted);
		}

		TEST_METHOD(Test_Array_reverse)
		{
			Array<int> arr;
			for (int i = 0; i < 10; i++)
			{
				arr.pushBack(i);
			}
			arr.reverse(0, 9);
			bool isReversed = true;
			for (int i = 1; i < 10; i++)
			{
				if (arr[i] > arr[i - 1])
				{
					isReversed = false;
				}
			}
			Assert::AreEqual(true, isReversed);
		}

		TEST_METHOD(Test_Array_insert)
		{
			Array<int> arr;
			for (int i = 0; i < 10; i++)
			{
				arr.pushBack(i);
			}
			arr.insert(5, 10);
			for (int i = 0; i < 5; i++)
			{
				Assert::AreEqual(i, arr[i]);
			}
			Assert::AreEqual(10, arr[5]);
			for (int i = 6; i < 11; i++)
			{
				Assert::AreEqual(i - 1, arr[i]);
			}
		}

		TEST_METHOD(Test_Array_erase)
		{
			Array<int> arr;
			for (int i = 0; i < 10; i++)
			{
				arr.pushBack(i);
			}
			arr.erase(5);
			for (int i = 0; i < 5; i++)
			{
				Assert::AreEqual(i, arr[i]);
			}
			for (int i = 5; i < 9; i++)
			{
				Assert::AreEqual(i + 1, arr[i]);
			}
		}

	};

	TEST_CLASS(BasicFunctionality_Exceptions)
	{
	public:

		TEST_METHOD(Test_Array_erase_Exception)
		{
			Array<int> arr;
			for (int i = 0; i < 10; i++)
			{
				arr.pushBack(i);
			}
			bool exceptionIsCatched = false;
			try
			{
				arr.erase(10);
			}
			catch (std::out_of_range)
			{
				exceptionIsCatched = true;
			}
			Assert::AreEqual(true, exceptionIsCatched);
		}

		TEST_METHOD(Test_Array_insert_Exception)
		{
			Array<int> arr;
			for (int i = 0; i < 10; i++)
			{
				arr.pushBack(i);
			}
			bool exceptionIsCatched = false;
			try
			{
				arr.insert(10, 10);
			}
			catch (std::out_of_range)
			{
				exceptionIsCatched = true;
			}
			Assert::AreEqual(true, exceptionIsCatched);
		}

		TEST_METHOD(Test_Array_reverse_Exceptions)
		{
			Array<int> arr;
			for (int i = 0; i < 10; i++)
			{
				arr.pushBack(i);
			}
			int exceptionIsCatched = 0;
			try
			{
				arr.reverse(0, 10);
			}
			catch (std::invalid_argument)
			{
				exceptionIsCatched++;
			}
			try
			{
				arr.reverse(-1, 9);
			}
			catch (std::invalid_argument)
			{
				exceptionIsCatched++;
			}
			try
			{
				arr.reverse(-2, -1);
			}
			catch (std::invalid_argument)
			{
				exceptionIsCatched++;
			}
			try
			{
				arr.reverse(5, 4);
			}
			catch (std::invalid_argument)
			{
				exceptionIsCatched++;
			}
			try
			{
				arr.reverse(10, 11);
			}
			catch (std::invalid_argument)
			{
				exceptionIsCatched++;
			}
			Assert::AreEqual(5, exceptionIsCatched);
			arr.reverse(5, 5);
			for (int i = 0; i < 10; i++)
			{
				Assert::AreEqual(i, arr[i]);
			}
		}

		TEST_METHOD(Test_Array_sort_Exceptions)
		{
			Array<int> arr;
			for (int i = 0; i < 10; i++)
			{
				arr.pushBack(i);
			}
			int exceptionIsCatched = 0;
			try
			{
				arr.sort(0, 10);
			}
			catch (std::invalid_argument)
			{
				exceptionIsCatched++;
			}
			try
			{
				arr.sort(-1, 9);
			}
			catch (std::invalid_argument)
			{
				exceptionIsCatched++;
			}
			try
			{
				arr.sort(-2, -1);
			}
			catch (std::invalid_argument)
			{
				exceptionIsCatched++;
			}
			try
			{
				arr.sort(5, 4);
			}
			catch (std::invalid_argument)
			{
				exceptionIsCatched++;
			}
			try
			{
				arr.sort(10, 11);
			}
			catch (std::invalid_argument)
			{
				exceptionIsCatched++;
			}
			Assert::AreEqual(5, exceptionIsCatched);
			arr.sort(5, 5);
			for (int i = 0; i < 10; i++)
			{
				Assert::AreEqual(i, arr[i]);
			}
		}

		TEST_METHOD(Test_Array_swap_OutOfRangeException)
		{
			Array<int> arr;
			for (int i = 0; i < 10; i++)
			{
				arr.pushBack(i);
			}
			bool exceptionIsCatched = false;
			try
			{
				arr.swap(0, 10);
			}
			catch (std::out_of_range)
			{
				exceptionIsCatched = true;
			}
			Assert::AreEqual(true, exceptionIsCatched);
		}

		TEST_METHOD(Test_Array_popBack_EmptyArrayException)
		{
			Array<int> arr;
			bool exceptionIsCatched = false;
			try
			{
				arr.popBack();
			}
			catch (std::out_of_range)
			{
				exceptionIsCatched = true;
			}
			Assert::AreEqual(true, exceptionIsCatched);
		}
	};
}