#include "MailBox.h"
#include "ViewWPF.h";

using namespace DrawProject;

void MailBox::SendMessage(Message* message) {

	messageQueue.push(message);
	std::ofstream log("logs.txt", std::ios::app);
	log << "push(" << message->code << ")\n";
	log.close();
}

Message* MailBox::GetMessage() {
	if (messageQueue.empty()) {
		throw std::exception("messageQueue is empty");
	}
	auto message = messageQueue.front();

	std::ofstream log("logs.txt", std::ios::app);
	log << "pop(" << message->code << ")\n";
	log.close();

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
	auto viewWPF = ViewWPF::GetInstance();
	viewWPF->Run();
}
MailBox* MailBox::instance = nullptr;

