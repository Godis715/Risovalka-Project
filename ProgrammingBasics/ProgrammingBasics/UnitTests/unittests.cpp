#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Include/Array.h"
#include "../Include/Dictionary.h"
#include "../Include/hidden/list_util(hidden).h"
#include "../Include/List.h"
#include "../Include/Requirement.h"
#include "../Include/HyperGraph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(List_BasicFunctionality)
	{
	public:

		TEST_METHOD(Test_List_Marker_moveNext)
		{
			List<int> tempList;
			for (int i = 0; i < 10; i++)
			{
				tempList.addElementAfterTail(i);
			}
			auto tempMarker = tempList.createMarker();
			for (int i = 0; i < 10; i++)
			{
				Assert::AreEqual(i, tempMarker->getCurrent());
				tempMarker->moveNext();
			}
		}

		TEST_METHOD(Test_List_Marker_getCurrent)
		{
			List<int> tempList;
			for (int i = 0; i < 10; i++)
			{
				tempList.addElementAfterTail(i);
			}
			auto tempMarker = tempList.createMarker();
			Assert::AreEqual(0, tempMarker->getCurrent());
		}

		TEST_METHOD(Test_List_Marker_setCurrent)
		{
			List<int> tempList;
			for (int i = 0; i < 10; i++)
			{
				tempList.addElementAfterTail(i);
			}
			auto tempMarker = tempList.createMarker();
			tempMarker->moveNext();
			tempMarker->setCurrent(17);
			Assert::AreEqual(17, tempMarker->getCurrent());
		}

		TEST_METHOD(Test_List_Marker_moveTail)
		{
			List<int> tempList;
			int i;
			for (i = 0; i < 10; i++)
			{
				tempList.addElementAfterTail(i);
			}
			auto tempMarker = tempList.createMarker();
			tempMarker->moveTail();
			Assert::AreEqual(i - 1, tempMarker->getCurrent());
		}

		TEST_METHOD(Test_List_Marker_moveHead)
		{
			List<int> tempList;
			for (int i = 0; i < 10; i++)
			{
				tempList.addElementAfterTail(i);
			}
			auto tempMarker = tempList.createMarker();
			tempMarker->moveNext();
			tempMarker->moveHead();
			Assert::AreEqual(0, tempMarker->getCurrent());
		}

		TEST_METHOD(Test_List_Marker_addAfter)
		{
			List<int> tempList;
			for (int i = 0; i < 10; i++)
			{
				tempList.addElementAfterTail(i);
			}
			auto tempMarker = tempList.createMarker();
			tempMarker->addAfter(22);
			tempMarker->moveNext();
			Assert::AreEqual(22, tempMarker->getCurrent());
		}

		TEST_METHOD(Test_List_Marker_deleteAfter)
		{
			List<int> tempList;
			for (int i = 0; i < 10; i++)
			{
				tempList.addElementAfterTail(i);
			}
			auto tempMarker = tempList.createMarker();
			tempMarker->deleteAfter();
			tempMarker->moveNext();
			Assert::AreEqual(2, tempMarker->getCurrent());
		}

		TEST_METHOD(Test_List_getSize)
		{
			List<int> tempList;
			for (int i = 0; i < 10; i++)
			{
				tempList.addElementAfterTail(i);
			}
			Assert::AreEqual(10, tempList.getSize());
		}

		TEST_METHOD(Test_List_addElementBeforeHead)
		{
			List<int> tempList;
			auto tempMarker = tempList.createMarker();
			tempList.addElementBeforeHead(11);
			tempMarker->moveHead();
			Assert::AreEqual(11, tempMarker->getCurrent());
			tempList.addElementBeforeHead(12);
			tempMarker->moveHead();
			Assert::AreEqual(12, tempMarker->getCurrent());
		}

		TEST_METHOD(Test_List_addElementAfterTail)
		{
			List<int> tempList;
			auto tempMarker = tempList.createMarker();
			for (int i = 0; i < 10; i++)
			{
				tempList.addElementAfterTail(i);
				tempMarker->moveTail();
				Assert::AreEqual(i, tempMarker->getCurrent());
			}
		}

		TEST_METHOD(Test_List_deleteHeadElement)
		{
			List<int> tempList;
			for (int i = 0; i < 10; i++)
			{
				tempList.addElementAfterTail(i);
			}
			auto tempMarker = tempList.createMarker();
			for (int i = 0; i < 10; i++)
			{
				tempMarker->moveHead();
				Assert::AreEqual(i, tempMarker->getCurrent());
				tempList.deleteHeadElement();
			}
		}

		TEST_METHOD(Test_List_deleteTailElement)
		{
			List<int> tempList;
			for (int i = 0; i < 10; i++)
			{
				tempList.addElementAfterTail(i);
			}
			auto tempMarker = tempList.createMarker();
			for (int i = 9; i > 0; i--)
			{
				tempMarker->moveTail();
				Assert::AreEqual(i, tempMarker->getCurrent());
				tempList.deleteTailElement();
			}
		}

	};

	TEST_CLASS(List_utils)
	{
	public:
		TEST_METHOD(Test_List_BubleSort_NoNeed)
		{
			List<int> tempList;
			for (int i = 0; i < 10; i++)
			{
				tempList.addElementAfterTail(i);
			}
			BublesSort(tempList);
			auto tempMarker = tempList.createMarker();
			tempMarker->moveHead();
			for (int i = 0; i < 10; i++)
			{
				Assert::AreEqual(i, tempMarker->getCurrent());
				tempMarker->moveNext();
			}
		}

		TEST_METHOD(Test_List_BubleSort_Reverted)
		{
			List<int> tempList;
			for (int i = 9; i >= 0; i--)
			{
				tempList.addElementAfterTail(i);
			}
			BublesSort(tempList);
			auto tempMarker = tempList.createMarker();
			tempMarker->moveHead();
			for (int i = 0; i < 10; i++)
			{
				Assert::AreEqual(i, tempMarker->getCurrent());
				tempMarker->moveNext();
			}
		}

		TEST_METHOD(Test_List_BubleSort_Equal)
		{
			List<int> tempList;
			for (int i = 0; i < 10; i++)
			{
				tempList.addElementAfterTail(12);
			}
			BublesSort(tempList);
			auto tempMarker = tempList.createMarker();
			tempMarker->moveHead();
			for (int i = 0; i < 10; i++)
			{
				Assert::AreEqual(12, tempMarker->getCurrent());
				tempMarker->moveNext();
			}
		}
	};

	TEST_CLASS(Array_BasicFunctionality)
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

	TEST_CLASS(Array_Exceptions)
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

	TEST_CLASS(Dictionary_BasicFunctionality)
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
			dic.Add(5, 10);
			Assert::AreEqual(1, dic.getsize());
		}

		TEST_METHOD(Test_Dictionary_find)
		{
			Dict<char, int> dic;
			dic.Add('A', 10);
			bool a = dic.find('A');
			Assert::AreEqual(true, a);
		}

		TEST_METHOD(Test_Dictionary_findInBigDict)
		{
			Dict<char, int> dic;
			dic.Add('B', 10);
			dic.Add('A', 15);
			bool a = dic.find('A');
			Assert::AreEqual(true, a);
		}

		TEST_METHOD(Test_Dictionary_erase)
		{
			Dict<int, int> dic;
			dic.Add(5, 10);
			dic.Erase(5);
			Assert::AreEqual(0, dic.getsize());
		}

		TEST_METHOD(Test_Dictionary_erase_SomeElements)
		{
			Dict<int, int> dic;
			dic.Add(5, 10);
			dic.Add(2, 11);
			dic.Add(4, 12);
			dic.Add(3, 13);
			dic.Add(1, 23);
			dic.Add(8, 14);
			dic.Add(6, 15);
			dic.Add(7, 26);
			dic.Add(9, 16);
			dic.Erase(5);
			Assert::AreEqual(8, dic.getsize());
			Assert::IsFalse(dic.find(5));
		}

	};

	TEST_CLASS(ListE_BasicFunctionality)
	{
	public:

		TEST_METHOD(Test_ListE_GetSize)
		{
			ListE<int> list;
			Assert::AreEqual(0, list.GetSize());
			list.PushHead(1);
			Assert::AreEqual(1, list.GetSize());
			list.PushTail(2);
			Assert::AreEqual(2, list.GetSize());
			list.MoveHead();
			list.PushAfterCurrent(3);
			Assert::AreEqual(3, list.GetSize());
			list.MoveTail();
			list.PushBeforeCurrent(4);
			Assert::AreEqual(4, list.GetSize());
		}

		TEST_METHOD(Test_ListE_PushHead)
		{
			ListE<int> list;
			list.PushHead(1);
			Assert::AreEqual(1, list.GetSize());
			list.PushHead(2);
			Assert::AreEqual(2, list.GetSize());
			list.MoveHead();
			Assert::AreEqual(2, list.GetCurrent());
			list.MoveNext();
			Assert::AreEqual(1, list.GetCurrent());
		}

		TEST_METHOD(Test_ListE_PushAfterCurrent)
		{
			ListE<int> list;
			list.PushAfterCurrent(1);
			Assert::AreEqual(1, list.GetSize());
			Assert::AreEqual(1, list.GetCurrent());
			list.PushAfterCurrent(2);
			Assert::AreEqual(2, list.GetSize());
			list.MoveNext();
			Assert::AreEqual(2, list.GetCurrent());
		}

		TEST_METHOD(Test_ListE_PushBeforeCurrent)
		{
			ListE<int> list;
			list.PushBeforeCurrent(1);
			Assert::AreEqual(1, list.GetSize());
			Assert::AreEqual(1, list.GetCurrent());
			list.PushBeforeCurrent(2);
			Assert::AreEqual(2, list.GetSize());
			Assert::AreEqual(1, list.GetCurrent());
			list.MovePrev();
			Assert::AreEqual(2, list.GetCurrent());
		}

		TEST_METHOD(Test_ListE_PushTail)
		{
			ListE<int> list;
			list.PushTail(1);
			Assert::AreEqual(1, list.GetSize());
			list.MoveTail();
			Assert::AreEqual(1, list.GetCurrent());
			list.PushTail(2);
			Assert::AreEqual(2, list.GetSize());
			list.MoveTail();
			Assert::AreEqual(2, list.GetCurrent());
		}

		TEST_METHOD(Test_ListE_DeleteCurrent)
		{
			ListE<int> list;
			list.PushTail(1);
			list.PushTail(2);
			list.PushTail(3);
			list.MoveHead();
			list.MoveNext();
			list.DeleteCurrent();
			Assert::AreEqual(2, list.GetSize());
			list.MoveHead();
			list.DeleteCurrent();
			Assert::AreEqual(1, list.GetSize());
			list.MoveHead();
			list.DeleteCurrent();
			Assert::AreEqual(0, list.GetSize());
		}

		TEST_METHOD(Test_ListE_DeleteList)
		{
			ListE<int> list;
			list.PushHead(1);
			list.PushHead(2);
			list.DeleteList();
			Assert::AreEqual(0, list.GetSize());
			list.DeleteList();
			Assert::AreEqual(0, list.GetSize());
		}

		TEST_METHOD(Test_ListE_IsCurrent)
		{
			ListE<int> list;
			Assert::AreEqual(false, list.IsCurrent());
			list.PushHead(2);
			Assert::AreEqual(true, list.IsCurrent());
			list.DeleteList();
			Assert::AreEqual(false, list.IsCurrent());
		}

		TEST_METHOD(Test_ListE_GetCurrent)
		{
			ListE<int> list;
			list.PushTail(1);
			list.PushTail(2);
			list.PushTail(3);
			Assert::AreEqual(1, list.GetCurrent());
			list.MoveNext();
			Assert::AreEqual(2, list.GetCurrent());
			list.MoveNext();
			Assert::AreEqual(3, list.GetCurrent());
		}

		TEST_METHOD(Test_ListE_MoveHead)
		{
			ListE<int> list;
			list.PushTail(1);
			list.PushTail(2);
			list.MoveHead();
			Assert::AreEqual(1, list.GetCurrent());
		}

		TEST_METHOD(Test_ListE_MoveTail)
		{
			ListE<int> list;
			list.PushTail(1);
			list.PushTail(2);
			list.MoveTail();
			Assert::AreEqual(2, list.GetCurrent());
		}

		TEST_METHOD(Test_ListE_MoveNext)
		{
			ListE<int> list;
			list.PushTail(1);
			list.PushTail(2);
			Assert::AreEqual(1, list.GetCurrent());
			list.MoveNext();
			Assert::AreEqual(2, list.GetCurrent());
		}

		TEST_METHOD(Test_ListE_MovePrev)
		{
			ListE<int> list;
			list.PushTail(1);
			list.PushTail(2);
			list.MoveTail();
			Assert::AreEqual(2, list.GetCurrent());
			list.MovePrev();
			Assert::AreEqual(1, list.GetCurrent());
		}

	};

	/*TEST_CLASS(HyperGraph_BasicFuctionality)
	{
	public:

		TEST_METHOD(Test_HyperGraph_Add)
		{
			HyperGraph hg;
			Assert::AreEqual(0, hg.GetSize());
			Point p1(1, 1);
			Point p2(2, 2);
			Array<Primitive*> arp;
			arp.pushBack(&p1);
			arp.pushBack(&p2);
			DistanceBetweenPoints req(p1, p2, 5);
			hg.Add(&req, arp);
			Assert::AreEqual(1, hg.GetSize());
			Point p3(3, 3);
			Point p4(4, 4);
			Array<Primitive*> arp2;
			arp2.pushBack(&p3);
			arp2.pushBack(&p4);
			DistanceBetweenPoints req2(p3, p4, 2);
			hg.Add(&req2, arp2);
			Assert::AreEqual(2, hg.GetSize());
			DistanceBetweenPoints req1(p2, p4, 2);
			Array<Primitive*> arp1;
			arp1.pushBack(&p2);
			arp1.pushBack(&p4);
			hg.Add(&req1, arp1);
			Assert::AreEqual(1, hg.GetSize());
		}

		TEST_METHOD(Test_HyperGraph_SearchPrimitive)
		{
			HyperGraph hg;
			Point p1(1, 1);
			Point p2(2, 2);
			Array<Primitive*> arp;
			arp.pushBack(&p1);
			arp.pushBack(&p2);
			DistanceBetweenPoints req(p1, p2, 5);
			hg.Add(&req, arp);
			Assert::AreEqual(true, hg.SearchPrimitive(p1.GetID()));
			Assert::AreEqual(true, hg.SearchPrimitive(p2.GetID()));
			Point p3(3, 2);
			Assert::AreEqual(false, hg.SearchPrimitive(p3.GetID()));
		}

		TEST_METHOD(Test_HyperGraph_DeletePrimitive)
		{
			HyperGraph hg;
			Point p1(1, 1);
			Point p2(2, 2);
			Array<Primitive*> arp;
			arp.pushBack(&p1);
			arp.pushBack(&p2);
			DistanceBetweenPoints req(p1, p2, 5);
			hg.Add(&req, arp);
			hg.DeletePrimitive(p1.GetID());
			Assert::AreEqual(0, hg.GetSize());
		}

		TEST_METHOD(Test_HyperGraph_UploadingDataPrimitive)
		{

		}

		TEST_METHOD(Test_HyperGraph_UploadingDataRequirement)
		{

		}

	};*/
}