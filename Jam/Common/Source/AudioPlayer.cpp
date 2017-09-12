#include "AudioPlayer.h"
#include <cstdlib>
#include <windows.h>

int AudioPlayer::volume = 100;

/*******************************
CONSTRUCTORS
*******************************/
AudioPlayer::AudioPlayer()
{
	soundEngine = createIrrKlangDevice();
	currentSound = 0;

	if (!soundEngine)
	{
		cout << "Error: Could not create sound engine" << endl;
		exit(0);
	}

	fileName = "\0";
	//volume = 100;
	position = 0;
	soundEngine->setSoundVolume(1);
} 

AudioPlayer::AudioPlayer(string soundFile)
{
	soundEngine = createIrrKlangDevice();
	currentSound = 0;

	if (!soundEngine)
	{
		cout << "Error: Could not create sound engine" << endl;
		exit(0);
	}

	fileName = soundFile;
	//volume = 100;
	position = 0;
	soundEngine->setSoundVolume(1);
}

/*****************************
DESTRUCTOR
*****************************/
AudioPlayer::~AudioPlayer()
{
	if (soundEngine)
	soundEngine->drop();

	if (currentSound)
	currentSound->drop();

	for each (auto s in playlist)
		delete s;
}


/***************************
PLAY FUNCTIONS
***************************/
void AudioPlayer::playSound()
{
	if (fileName == "\0")
	{
		cout << "Error: No sound file selected" << endl;
		return;
	}

	currentSound = soundEngine->play2D(fileName.c_str(), false, false, true);

	if (!currentSound)
	{
		cout << "Error: Could not play file" << endl;
		exit(0);
	}

	while (!currentSound->isFinished())
		Sleep(100);

	position = currentSound->getPlayPosition();
}

void AudioPlayer::playSound(int milliseconds)
{
	if (fileName == "\0")
	{
		cout << "Error: No sound file selected" << endl;
		return;
	}

	currentSound = soundEngine->play2D(fileName.c_str(), false, false, true);

	if (!currentSound)
	{
		cout << "Error: Could not play file" << endl;
		exit(0);
	}

	Sleep(milliseconds);

	pause();
}

void AudioPlayer::playSound(string soundFile)
{
	setFileName(soundFile);

	currentSound = soundEngine->play2D(fileName.c_str(), false, false, true);

	if (!currentSound)
	{
		cout << "Error: Could not play file" << endl;
		exit(0);
	}


	while (!currentSound->isFinished())
		Sleep(100);

	position = currentSound->getPlayPosition();
}

void AudioPlayer::playSound(string soundFile, int milliseconds)
{
	setFileName(soundFile);

	currentSound = soundEngine->play2D(fileName.c_str(), false, false, true);

	if (!currentSound)
	{
		cout << "Error: Could not play file" << endl;
		exit(0);
	}

	Sleep(milliseconds);
	pause();
}

void AudioPlayer::playSoundThreaded()
{
	currentSound = soundEngine->play2D(fileName.c_str(), false, false, true);
	if (!currentSound)
	{
		cout << "Error: Could not play file" << endl;
		exit(0);
	}
	currentSound->setVolume((double)volume / 100.0);
}

void AudioPlayer::playSoundThreaded(std::string fileName)
{
	currentSound = soundEngine->play2D(fileName.c_str(), false, false, true);
	if (!currentSound)
	{
		cout << "Error: Could not play file" << endl;
		exit(0);
	}
	currentSound->setVolume((double)volume / 100.0);
}

void AudioPlayer::playSoundThreaded3D(std::string fileName, Vector3 pos)
{
	currentSound = soundEngine->play3D(fileName.c_str(), vec3df(pos.x, pos.y, pos.z), false, false, true);
	if (!currentSound)
	{
		cout << "Error: Could not play file" << endl;
		exit(0);
	}
}

bool AudioPlayer::isSoundPlaying()
{
	return !currentSound->isFinished();
}

void AudioPlayer::playLoop()
{
	currentSound = soundEngine->play2D(fileName.c_str(), true, false, true);
	if (!currentSound)
	{
		cout << "Error: Could not play file" << endl;
		exit(0);
	}
	currentSound->setVolume((double)volume / 100.0);
}


void AudioPlayer::playLoop(std::string fileName)
{
	currentSound = soundEngine->play2D(fileName.c_str(), true, false, true);
	if (!currentSound)
	{
		cout << "Error: Could not play file" << endl;
		exit(0);
	}
	currentSound->setVolume((double)volume / 100.0);
}
/************************
PAUSE/RESUME
************************/
void AudioPlayer::pause()
{
	/*position = currentSound->getPlayPosition();*/
	soundEngine->setAllSoundsPaused();
}

void AudioPlayer::resume()
{
	currentSound = soundEngine->play2D(fileName.c_str(), false, false, true);

	if (position != -1)
		currentSound->setPlayPosition(position);
}


/************************
GET/SET FILENAME
************************/
void AudioPlayer::setFileName(string soundFile)
{
	if (soundFile != "")
		fileName = soundFile;
}

string AudioPlayer::getFileName()
{
	return fileName;
}


/***************************
VOLUME CONTROL
***************************/
void AudioPlayer::setVolume(int newVolume)
{
	if (newVolume < 0 || newVolume > 100)
		volume = 50;
	else
		volume = newVolume;

	currentSound->setVolume(volume / 100.0);
}

void AudioPlayer::increaseVolume()
{
	volume += 10;

	if (volume > 100)
		volume = 100;
	currentSound->setVolume(volume / 100.0);
}

void AudioPlayer::increaseVolume(int increment)
{
	volume += increment;

	if (volume > 100)
		volume = 100;
	currentSound->setVolume(volume / 100.0);
}

void AudioPlayer::decreaseVolume()
{
	volume -= 10;

	if (volume < 0)
		volume = 0;
	currentSound->setVolume(volume / 100.0);
}

void AudioPlayer::decreaseVolume(int increment)
{
	volume -= increment;

	if (volume < 0)
		volume = 0;
	currentSound->setVolume(volume / 100.0);
}

int AudioPlayer::getCurrentVolume()
{
	return volume;
}