#pragma once

#include "ManagedObject.h"
#include "MailBox.h"

using namespace Kernel;

/*		Array<double> doubleArr;
		Array<int> intArr;
		Array<std::string> strArr;

		int code;*/

namespace KernelWrapper {
	ref class MessageWrapper : public ManagedObject<Message> {
	private:
		array<double>^ doubleArr;
		array<int>^ intArr;
	public:
		MessageWrapper(Message* mess) : ManagedObject(mess) {
			
		}

		array<double>^ GetDoubleArr() {
			return doubleArr;
		}
		array<int>^ GetIntArr() {
			return intArr;
		}

	};
}