#ifndef MNF_H
#define MNF_H

#include <iostream>
#include <exception>
#include <string>

class MeshNotFound : public std::exception
{
	std::string errStr;
public:
	MeshNotFound(std::string a)
	{
		errStr = a;
	}
	const char* what() const throw()
	{
		std::string wad = errStr + " Entity Not Found!";
		return wad.c_str();
	}
};

#endif