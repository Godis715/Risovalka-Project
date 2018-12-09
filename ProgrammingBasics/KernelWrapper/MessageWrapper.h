#pragma once

#include "ManagedObject.h"
#include "MailBox.h"

using namespace System;

using namespace Kernel;

using namespace System::Runtime::InteropServices;

namespace KernelWrapper 
{
	public ref class MessageWrapper : public ManagedObject<Message> 
	{
	private:
		array<double>^ doubleArr;
		array<int>^ intArr;
		String^ str;
	public:
		
		MessageWrapper(Message* mess) : ManagedObject(mess) 
		{
			
		}

		array<double>^ GetDoubleArr() 
		{
			return doubleArr;
		}

		array<int>^ GetIntArr() 
		{
			return intArr;
		}


	};
}