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
	std::ofstream imya("Log.txt");
	imya << "shto-to";
	imya.close();
	if (instance == nullptr) {

		instance = new MailBox;
	}
	return instance;
 }

MailBox::MailBox() {

}

void MailBox::InitKernel() {
	// initializing viewWPF -> initializing presenter -> initializing Model
	Logger::InitLogger(new std::ofstream("Log.txt"), 4);
	auto viewWPF = ViewWPF::GetInstance();
	viewWPF->Run();
}
MailBox* MailBox::instance = nullptr;

