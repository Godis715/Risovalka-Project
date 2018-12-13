#include "MailBox.h"
#include "ViewWPF.h";

using namespace DrawProject;

void MailBox::SendMessage(Message* message) {
	messageQueue.push(message);
}

Message* MailBox::GetMessage() {
	if (messageQueue.empty()) {
		throw std::exception("messageQueue is empty");
	}

	auto message = messageQueue.front();
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

	Logger::InitLogger(new std::ofstream("Log.txt"), 3);
	LOG("1", LEVEL_4);
	auto viewWPF = ViewWPF::GetInstance();
	viewWPF->Run();
}
MailBox* MailBox::instance = nullptr;

