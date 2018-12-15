#pragma once

#include "ManagedObject.h"
#include "MailBox.h"
#include "Converter.h"
#include "MessageWrapper.h"

using namespace System;

using namespace Kernel;

namespace KernelWrapper {
	public ref class MailBoxWrapper : public ManagedObject<MailBox>
	{
	public:
		MailBoxWrapper() : ManagedObject(MailBox::GetInstance()) 
		{
			auto mailBox = MailBox::GetInstance();
			mailBox->InitKernel();
		}

		void SendEvent(int code, array<double>^ doubleArr, String^ str) 
		{
			instance->SendEvent(
				code,
				Helpers::Converter::ToDrawProjArray(doubleArr),
				Helpers::Converter::ToStdString(str)
			);
		}

		void SendEvent(int code, array<double>^ doubleArr) 
		{
			if (code == 1) {
				int b = 5;
			}
			instance->SendEvent(code,
				Helpers::Converter::ToDrawProjArray(doubleArr));
		}

		bool IsEmpty() 
		{
			// needs to check nullptr
			return instance->Empty();
		}

		MessageWrapper^ GetMessage() 
		{
			Message* mess = instance->GetMessage();
			return gcnew MessageWrapper(mess);
		}

	private:
	};
}

