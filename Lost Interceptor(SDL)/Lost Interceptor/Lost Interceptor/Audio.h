#pragma once

#include <SDL.h>
#include <SDL_audio.h>
#include <stdio.h>
#include <string>

class Audio
{
public:
	Audio();
	~Audio();
	void play(int choice);
	
private:
	SDL_AudioDeviceID deviceId;
	SDL_AudioSpec wavSpec;
	Uint8* wavBuffer; 
	Uint32 wavLength; 
};
