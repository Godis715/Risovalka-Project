#include "MailBox.h"



MailBox::MailBox()
{
}


MailBox::~MailBox()
{
}

RequestClass RequestController::_NewRequest() {
	return RequestClass(new std::string(""));
}

LineClass DrawClass::Line() {
	Add("line");
	return LineClass(request);
}
PointClass DrawClass::Point() {
	Add("point");
	return PointClass(request);
}
SegmentClass DrawClass::Segment() {
	Add("segment");
	return SegmentClass(request);
}
CircleClass DrawClass::Circle() {
	Add("circle");
	return CircleClass(request);
}

DrawClass RequestClass::Draw() {
	Add("draw");
	return DrawClass(request);
}

PutInfoClass RequestClass::PutInfo() {
	Add("put");
	return PutInfoClass(request);
}

StateClass PutInfoClass::State() {
	Add("state");
	return StateClass(request);
}
