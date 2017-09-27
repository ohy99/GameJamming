#include "Loader.h"

Loader::Loader() : 
	start_of_pattern("============ Pattern ============"),
	end_of_pattern("========== Pattern End ==========")
{
}

Loader::~Loader()
{
}

bool Loader::load_pattern(vecVecVec & vec, char * file_path)
{
	//binary : open in binary. app : all output operations are performed at the end of the file
	std::ifstream fileStream(file_path, std::ios::binary);
	if (!fileStream.is_open()) {
		std::cout << "Impossible to open " << file_path << ". Are you in the right directory ?\n";
		return false;
	}

	int current_pattern_index = 0;
	int current_path_index = 0;
	while (!fileStream.eof()) {
		char buf[256];
		fileStream.getline(buf, 256);
		if (strncmp(start_of_pattern.c_str(), buf, start_of_pattern.size()) == 0)
		{
			//sscanf_s((buf + 11), "%d", &charWidth);
			load_this_pattern(vec, fileStream, buf);
		}
	}


	fileStream.close();
}

void Loader::load_this_pattern(vecVecVec & vec, std::ifstream & fileStream, char * buf)
{
	//mark the start of pattern
	vec.push_back(vecVec());
	while (std::strcmp(buf, (end_of_pattern).c_str()) != 0 && std::strcmp(buf, (end_of_pattern + "\r").c_str()) != 0)
	{
		fileStream.getline(buf, 256);
		load_this_path(vec, fileStream, buf);
	}
}

void Loader::load_this_path(vecVecVec & vec_, std::ifstream & fileStream, char * buf)
{
	Vector3 temp;

	vec_.back().push_back(vec());
	vec* current_path = &vec_.back().back();

	while (std::strlen(buf) > 0 && std::strcmp(buf, (end_of_pattern).c_str()) != 0)
	{
		if (sscanf_s((buf), "[ %f, %f, %f ]", &temp.x, &temp.y, &temp.z) == 3)
		{
			current_path->push_back(temp);
			fileStream.getline(buf, 256);
		}
		else
			break;
	}


}
