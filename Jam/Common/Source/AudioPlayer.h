#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <string>
#include <map>
#include "sound.h"
#include "Vector3.h"
#include "SingletonTemplate.h"
//#include "irrKlang.h"
//#include "ik_vec3d.h"
#include "../../irrKlang/include/ik_vec3d.h"
#include "../../irrKlang/include/irrKlang.h"

#pragma comment(lib, "irrklang.lib")

class AudioPlayer : public Singleton<AudioPlayer>
{
	friend Singleton<AudioPlayer>;
private:
	irrklang::ISoundEngine* soundEngine;
	irrklang::ISound* backgroundSound;
	static int volume;
	int position;

	//map of all sounds
	//name, file
	std::map<std::string, std::string>m_playlist;
public:
	AudioPlayer();
	~AudioPlayer();

	//loading all sounds and all names to the playlist
	void Init();

	//parameters are the name, volume is a value from 0 to 1
	void PlaySound2D(std::string name, float volume = -1);
	//parameters are the name, volume is a value from 0 to 1
	void PlayBackground2D(std::string name, float volume = -1);

	// Volume controls
	void setVolume(int newVolume);
	void increaseVolume();
	void increaseVolume(int increment);
	void decreaseVolume();
	void decreaseVolume(int increment);
	int getCurrentVolume();
};

#endif //!AUDIOPLAYER_H