#include "MessageDispatcher.h"
#include "GameObject.h"

void MessageDispatcher::Init()
{
}

bool MessageDispatcher::Send(std::string address, BaseMessage* msg)
{
	if (addressMap[address] != nullptr) {
		addressMap[address]->Handle(msg);
		return true;
	}
	else {
		printf("Address does not exist: %s\n", address);
		return false;
	}
}

bool MessageDispatcher::Register(std::string address, MessageHandle* go)
{
	if (addressMap[address] == nullptr) {
		addressMap[address] = go;
		return true;
	}
	else {
		printf("Address already occupied!\n");
		return false;
	}
}
