/*	
	N3cr0nhym 13.09.2019.

	A bare bones CLI music player made with SDL2
	Only supports WAV format.
*/
#include "include/SDL.h"
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <term.h>
//Plays WAV file.
void PlayWav(char* AudioFile)
	{		
		//Initiates SDL_AUDIO
		if(SDL_Init(SDL_INIT_AUDIO) !=0)
			{
				std::cout<<"ERROR: Cannot initaite SDL_AUDIO"<<std::endl;
			}
		//Declares local Variabls:
		SDL_AudioSpec wavSpec;
		Uint32 wavLength;
		Uint8 *wavBuffer;
		//Loads WAV File:
		std::cout<<"Loading: "<<AudioFile<<std::endl;		
		if(SDL_LoadWAV(AudioFile, &wavSpec, &wavBuffer, &wavLength)==NULL)
			{
				std::cout<<"ERROR: Cannot load"<<AudioFile<<std::endl;
			}
		//Oepns audio devid:
		SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
		if( deviceId == 0 )
			{
				std::cout<<"ERROR: Failed to open audio device"<<std::endl;
			}
		//Queues Audio:
		if( SDL_QueueAudio(deviceId, wavBuffer, wavLength) != 0 )
			{
				std::cout<<"ERROR: Failed to open audio device" <<std::endl;
			}
		//Unpauses Queue and plays song		
		SDL_PauseAudioDevice(deviceId, 0);
		time_t timer;
		double start = time(&timer);
		//Delays for duration of song that if figures out form nubmer of bits freq and numebr of channels:		
		while( (double)difftime(time(&timer), start)*1000 < ((wavLength/wavSpec.freq)*(500/(int)wavSpec.channels)))
			{	
				int t=0;
				std::system("clear");
				std::cout<<"Playing: "<<AudioFile<<std::endl;		
				std::cout<<"[";				
				for(  int i=0; i<(int)(((double)difftime(time(&timer), start)/((wavLength/wavSpec.freq)*(500/(int)wavSpec.channels)))*100000); i=i+5)
					{
						std::cout<< "#";
						t=(i/5)+1;					
					}		
				for( int i =0; i <= 20-t; i++ )
					{
						std::cout<<" ";
					}
				std::cout<<"]";
				std::cout<<(int)(((double)difftime(time(&timer), start)/((wavLength/wavSpec.freq)*(500/(int)wavSpec.channels)))*100000) <<"%"<<std::endl;			
				SDL_Delay(1000);
			}
		//Cleans up memory:
		SDL_CloseAudioDevice(deviceId);
		SDL_FreeWAV(wavBuffer);
		SDL_Quit();
	}
int main(int argc, char* argv[])
	{
		for(int i=1; i < argc; i++)
			{
				PlayWav(argv[i]);
			}		
		return 0;
	}
