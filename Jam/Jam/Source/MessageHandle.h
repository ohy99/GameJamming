#ifndef MESSAGE_HANDLE_H
#define MESSAGE_HANDLE_H

class BaseMessage;
class MessageHandle {
public:
	virtual void Handle(BaseMessage* msg) {};

	MessageHandle() {}
	virtual ~MessageHandle(){}
};

#endif