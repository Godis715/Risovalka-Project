#pragma once

#include "ManagedObject.h"
#include "MailBox.h"

using namespace System;

using namespace Kernel;

namespace KernelWrapper {
	public ref class MailBoxWrapper : public ManagedObject<MailBox> {
	public:
		MailBoxWrapper() : ManagedObject(MailBox::GetInstance()) 
		{
			
		}

		void SendEvent(/*args*/) {
			instance->SendEvent(/*args*/);
		}

	private:
	};
}

