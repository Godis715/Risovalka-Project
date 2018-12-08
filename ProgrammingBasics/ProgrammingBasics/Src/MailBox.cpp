#include "MailBox.h"
#include "ViewWPF.h";

using namespace Kernel;
using namespace DrawProject;

void MailBox::SendMessage(const Message& message) {
	messageQueue.push(message);
}

Message MailBox::GetMessage() {
	if (messageQueue.empty()) {
		throw std::exception("messageQueue is empty");
	}
	auto message = messageQueue.back();
	messageQueue.pop();
	return message;
}

bool MailBox::Empty() {
	return messageQueue.empty();
}

MailBox* MailBox::GetInstance() {
	if (instance == nullptr) {
		instance = new MailBox;
	}
	return instance;
 }

MailBox::MailBox() {

}

void MailBox::InitKernel() {
	// initializing viewWPF -> initializing presenter -> initializing Model
	ViewWPF::GetInstance();
}

MailBox* MailBox::instance = nullptr;

