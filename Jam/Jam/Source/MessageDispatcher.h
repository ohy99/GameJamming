#ifndef MESSAGE_DISPATCHER_H
#define MESSAGE_DISPATCHER_H

#include "SingletonTemplate.h"
#include <string>
#include <map>

#include "MessageHandle.h"

class BaseMessage;
class GameObject;
class MessageDispatcher : public Singleton<MessageDispatcher>{
	friend Singleton<MessageDispatcher>;
public:
	void Init();
	bool Send(std::string address, BaseMessage* msg);

	bool Register(std::string address, MessageHandle* go);
private:
	std::map<std::string, MessageHandle*> addressMap;
};

#endif