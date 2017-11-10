#include "AudioPlayer.h"
//#include "AudioPlayer.h"
//#include <cstdlib>
//#include <windows.h>
//
//int AudioPlayer::volume = 100;
//
///*******************************
//CONSTRUCTORS
//*******************************/
//AudioPlayer::AudioPlayer()
//{
//	soundEngine = irrklang::createIrrKlangDevice();
//	currentSound = 0;
//
//	if (!soundEngine)
//	{
//		printf("Sound Engine creation failed\n");
//		exit(0);
//	}
//
//	fileName = "\0";
//	//volume = 100;
//	position = 0;
//	soundEngine->setSoundVolume(1);
//} 
//
//AudioPlayer::AudioPlayer(std::string soundFile)
//{
//	soundEngine = irrklang::createIrrKlangDevice();
//	currentSound = 0;
//
//	if (!soundEngine)
//	{
//		printf("Sound Engine creation failed\n");
//		exit(0);
//	}
//
//	fileName = soundFile;
//	//volume = 100;
//	position = 0;
//	soundEngine->setSoundVolume(1);
//}
//
///*****************************
//DESTRUCTOR
//*****************************/
//AudioPlayer::~AudioPlayer()
//{
//	if (soundEngine)
//	soundEngine->drop();
//
//	if (currentSound)
//	currentSound->drop();
//
//	for each (auto s in playlist)
//		delete s;
//}
//
//
///***************************
//PLAY FUNCTIONS
//***************************/
//void AudioPlayer::playSound()
//{
//	if (fileName == "\0")
//	{
//		printf("No sound file selected\n");
//		return;
//	}
//
//	currentSound = soundEngine->play2D(fileName.c_str(), false, false, true);
//
//	if (!currentSound)
//	{
//		printf("Unable to play selected sound: \n");
//		exit(0);
//	}
//
//	while (!currentSound->isFinished())
//		Sleep(100);
//
//	position = currentSound->getPlayPosition();
//}
//
//void AudioPlayer::playSound(int milliseconds)
//{
//	if (fileName == "\0")
//	{
//		printf("No sound file selected\n");
//		return;
//	}
//
//	currentSound = soundEngine->play2D(fileName.c_str(), false, false, true);
//
//	if (!currentSound)
//	{
//		printf("Unable to play selected sound: \n");
//		exit(0);
//	}
//
//	Sleep(milliseconds);
//
//	pause();
//}
//
//void AudioPlayer::playSound(std::string soundFile)
//{
//	setFileName(soundFile);
//
//	currentSound = soundEngine->play2D(fileName.c_str(), false, false, true);
//
//	if (!currentSound)
//	{
//		printf("Unable to play selected sound: \n");
//		exit(0);
//	}
//
//
//	while (!currentSound->isFinished())
//		Sleep(100);
//
//	position = currentSound->getPlayPosition();
//}
//
//void AudioPlayer::playSound(std::string soundFile, int milliseconds)
//{
//	setFileName(soundFile);
//
//	currentSound = soundEngine->play2D(fileName.c_str(), false, false, true);
//
//	if (!currentSound)
//	{
//		printf("Unable to play selected sound: \n");
//		exit(0);
//	}
//
//	Sleep(milliseconds);
//	pause();
//}
//
//void AudioPlayer::playSoundThreaded()
//{
//	currentSound = soundEngine->play2D(fileName.c_str(), false, false, true);
//	if (!currentSound)
//	{
//		printf("Unable to play selected sound: \n");
//		exit(0);
//	}
//	currentSound->setVolume((double)volume / 100.0);
//}
//
//void AudioPlayer::playSoundThreaded(std::string fileName)
//{
//	currentSound = soundEngine->play2D(fileName.c_str(), false, false, true);
//	if (!currentSound)
//	{
//		printf("Unable to play selected sound: \n");
//		exit(0);
//	}
//	currentSound->setVolume((double)volume / 100.0);
//}
//
//void AudioPlayer::playSoundThreaded3D(std::string fileName, Vector3 pos)
//{
//	currentSound = soundEngine->play3D(fileName.c_str(), irrklang::vec3df(pos.x, pos.y, pos.z), false, false, true);
//	if (!currentSound)
//	{
//		printf("Unable to play selected sound: \n");
//		exit(0);
//	}
//}
//
//bool AudioPlayer::isSoundPlaying()
//{
//	return !currentSound->isFinished();
//}
//
//void AudioPlayer::playLoop()
//{
//	currentSound = soundEngine->play2D(fileName.c_str(), true, false, true);
//	if (!currentSound)
//	{
//		printf("Unable to play selected sound: \n");
//		exit(0);
//	}
//	currentSound->setVolume((double)volume / 100.0);
//}
//
//
//void AudioPlayer::playLoop(std::string fileName)
//{
//	currentSound = soundEngine->play2D(fileName.c_str(), true, false, true);
//	if (!currentSound)
//	{
//		printf("Unable to play selected sound: \n");
//		exit(0);
//	}
//	currentSound->setVolume((double)volume / 100.0);
//}
///************************
//PAUSE/RESUME
//************************/
//void AudioPlayer::pause()
//{
//	/*position = currentSound->getPlayPosition();*/
//	soundEngine->setAllSoundsPaused();
//}
//
//void AudioPlayer::resume()
//{
//	currentSound = soundEngine->play2D(fileName.c_str(), false, false, true);
//
//	if (position != -1)
//		currentSound->setPlayPosition(position);
//}
//
//
///************************
//GET/SET FILENAME
//************************/
//void AudioPlayer::setFileName(std::string soundFile)
//{
//	if (soundFile != "")
//		fileName = soundFile;
//}
//
//std::string AudioPlayer::getFileName()
//{
//	return fileName;
//}
//
//
///***************************
//VOLUME CONTROL
//***************************/
//void AudioPlayer::setVolume(int newVolume)
//{
//	if (newVolume < 0 || newVolume > 100)
//		volume = 50;
//	else
//		volume = newVolume;
//
//	currentSound->setVolume(volume / 100.0);
//}
//
//void AudioPlayer::increaseVolume()
//{
//	volume += 10;
//
//	if (volume > 100)
//		volume = 100;
//	currentSound->setVolume(volume / 100.0);
//}
//
//void AudioPlayer::increaseVolume(int increment)
//{
//	volume += increment;
//
//	if (volume > 100)
//		volume = 100;
//	currentSound->setVolume(volume / 100.0);
//}
//
//void AudioPlayer::decreaseVolume()
//{
//	volume -= 10;
//
//	if (volume < 0)
//		volume = 0;
//	currentSound->setVolume(volume / 100.0);
//}
//
//void AudioPlayer::decreaseVolume(int increment)
//{
//	volume -= increment;
//
//	if (volume < 0)
//		volume = 0;
//	currentSound->setVolume(volume / 100.0);
//}
//
//int AudioPlayer::getCurrentVolume()
//{
//	return volume;
//}

AudioPlayer::AudioPlayer()
{
	soundEngine = irrklang::createIrrKlangDevice();
	if (!soundEngine) {
		printf("Sound Engine creation failed\n");
		exit(0);
	}

	position = 0;
	backgroundSound = nullptr;
	soundEngine->setSoundVolume(1);
}

AudioPlayer::~AudioPlayer()
{
	if (soundEngine)
		soundEngine->drop();

	if (backgroundSound)
		backgroundSound->drop();
}

void AudioPlayer::Init()
{
	m_playlist["Yaruta"] = "Audio//YARUTA.mp3";
	m_playlist["Power Bots"] = "Audio//Power Bots Loop.wav";
}

void AudioPlayer::PlaySound2D(std::string name, float volume)
{
	//getting the file name for the name of the sound
	std::string fileName = m_playlist[name];

	if (fileName == "\0") {
		printf("Sound name does not exist, are you sure you input the correct name?\nName:%s\n", name);
		return;
	}

	irrklang::ISound* sound = soundEngine->play2D(fileName.c_str(), false, false, true);

	if (sound == nullptr) {
		printf("Sound file for associated name does not exist.\n");
		std::cout << "Name: " << name << std::endl;
		return;
	}

	if (volume == -1) {
		sound->setVolume(1);
	}
	else {
		sound->setVolume(volume);
	}
}

void AudioPlayer::PlayBackground2D(std::string name, float volume)
{
	std::string fileName = m_playlist[name];

	if (fileName == "\0") {
		printf("Sound name does not exist, are you sure you input the correct name?\nName:%s\n", name);
		return;
	}

	irrklang::ISound* sound = soundEngine->play2D(fileName.c_str(), false, false, true);

	if (sound == nullptr) {
		printf("Sound file for associated name does not exist.\n");
		std::cout << "Name: " << name << std::endl;
		return;
	}

	if (backgroundSound) {
		backgroundSound->stop();
		backgroundSound->drop();
	}
	backgroundSound = sound;
	if (volume == -1) {
		sound->setVolume(1);
	}
	else {
		sound->setVolume(volume);
	}
}

void AudioPlayer::setVolume(int newVolume)
{
}

void AudioPlayer::increaseVolume()
{
}

void AudioPlayer::increaseVolume(int increment)
{
}

void AudioPlayer::decreaseVolume()
{
}

void AudioPlayer::decreaseVolume(int increment)
{
}

int AudioPlayer::getCurrentVolume()
{
	return 0;
}
