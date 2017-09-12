#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include "sound.h"
#include "Vector3.h"
//#include "irrKlang.h"
//#include "ik_vec3d.h"
#include "../../irrKlang/include/ik_vec3d.h"
#include "../../irrKlang/include/irrKlang.h"

#pragma comment(lib, "irrklang.lib")

using namespace std;
using namespace irrklang;

class AudioPlayer
{
private:
		ISoundEngine* soundEngine;
		ISound* currentSound;
		string fileName;
		static int volume;
		//static std::vector<
		int position;
public:
		AudioPlayer();
		AudioPlayer(string soundFile); // Doesn't play sound, only initializes fileName
		~AudioPlayer();

		//vector of sound file names
		std::vector<Sound*> playlist;

		/* All play functions STOP execution of the program except
		* playSoundThreaded(). Note: It isn't really multi-threaded.*/
		void playSound(); // Plays entire sound file
		void playSound(int milliseconds); // Plays for X number of milliseconds
		void playSound(string soundFile); // Play entire specified sound file
		void playSound(string soundFile, int milliseconds);
		void playSoundThreaded(); // Starts playing sound but program continues
		void playSoundThreaded(std::string fileName); //overloaded sound playing
		void playSoundThreaded3D(std::string fileName, Vector3 pos);
		bool isSoundPlaying(); // True = music is playing
		void playLoop();
		void playLoop(std::string fileName);
		// Pause/Resume, works like any other media player
		void pause();
		void resume();
		// Set/get sound file to be played/playing
		void setFileName(string soundFile);
		string getFileName();

		// Volume controls
		void setVolume(int newVolume);
		void increaseVolume();
		void increaseVolume(int increment);
		void decreaseVolume();
		void decreaseVolume(int increment);
		int getCurrentVolume();
};

#endif //!AUDIOPLAYER_H