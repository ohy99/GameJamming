#ifndef LOADER_H
#define LOADER_H

#include "SingletonTemplate.h"
#include <vector>
#include "Vector3.h"
#include <fstream>

class Loader : public Singleton<Loader>
{
public :
	typedef std::vector<Vector3> vec;//path
	typedef std::vector<vec> vecVec;//pattern
	typedef std::vector<vecVec> vecVecVec;//all patterns
private:
	friend Singleton;
	
	void load_this_pattern(vecVecVec & vec, std::ifstream& fileStream, char * buf);
	void load_this_path(vecVecVec & vec, std::ifstream& fileStream, char * buf);
public:
	bool load_pattern(vecVecVec & vec, char* file_path = "Image//enemy_spawn_pattern.txt");

	const std::string start_of_pattern;
	const std::string end_of_pattern;
protected:
	Loader();
	~Loader();
};

#endif // !LOADER_H

