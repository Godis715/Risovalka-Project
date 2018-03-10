#include "stdafx.h"
#include "CppUnitTest.h"
#include "../List/Include/List.h"
#include "../List/Include/list_util.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace List_tests
{		
	TEST_CLASS(BasicFunctionality)
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
}