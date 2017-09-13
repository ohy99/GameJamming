#ifndef MYDEBUGGER_H
#define MYDEBUGGER_H

#include "SingletonTemplate.h"
#include <map>
#include <sstream>
#include "Vector3.h"

class MyDebugger : public Singleton<MyDebugger>
{
	friend Singleton<MyDebugger>;

	std::map<std::string , std::stringstream> debug_info;
	Vector3 text_scale;
	
public:
	template <typename T>
	void watch_this_info(std::string Tag, T info);
	void render_debug_info();
protected:
	MyDebugger();
	~MyDebugger();
};

#endif // !MYDEBUGGER_H

template<typename T>
inline void MyDebugger::watch_this_info(std::string Tag, T info)
{
	int count = 0;
	while (debug_info.find(Tag) != debug_info.end()) {
		Tag = Tag + std::to_string(++count);
	}
	std::stringstream ss;
	ss << std::fixed;
	ss.precision(2);
	ss << info;
	debug_info[Tag] = ss;
}
