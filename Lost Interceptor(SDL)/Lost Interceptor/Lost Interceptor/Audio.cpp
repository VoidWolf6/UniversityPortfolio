#include "Audio.h"


Audio::Audio()
{
	SDL_Init(SDL_INIT_AUDIO);

	SDL_LoadWAV("Assets/Ambience.wav", &wavSpec, &wavBuffer, &wavLength);

	deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
}

Audio::~Audio()
{
	SDL_CloseAudioDevice(deviceId);
	SDL_FreeWAV(wavBuffer);
}

void Audio::play(int choice)
{
	switch (choice)
	{
	case 0:
		SDL_QueueAudio(deviceId, wavBuffer, wavLength);
		SDL_PauseAudioDevice(deviceId, 0);
	case 1:
		
	case 2:

	default:
		break;
	}
}


