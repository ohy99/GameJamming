#ifndef SOUND_H
#define SOUND_H

#include <string>

struct Sound
{
	Sound::Sound(std::string fileName) : fileName_(fileName) {};

	std::string fileName_;
};

#endif // !SOUND_H
