#include <SDL3/SDL.h>
#include <SDL3/SDL_audio.h>
#include "app.h"



int initApp(App *app, char caption[], int width, int height) {
    SDL_Init(SDL_INIT_VIDEO);     
    SDL_Init(SDL_INIT_AUDIO);     

    app->window = SDL_CreateWindow(
        caption,// window title
        width,// width, in pixels
        height,// height, in pixels
        0 // flags - see below
    );

    // Check that the window was successfully created
    if (app->window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    app->renderer = SDL_CreateRenderer(app->window, NULL);
    SDL_SetRenderDrawBlendMode(app->renderer, SDL_BLENDMODE_BLEND); 

	return 0;
}

void destroyApp(App *app) {
    // SDL_CloseAudioDevice(app->_audioDeviceID);
    SDL_DestroyWindow(app->window);
    SDL_Quit();
}

void playSound(App *app, char filePath[]){
	SDL_AudioSpec spec;

	if (SDL_LoadWAV(filePath, &spec, &app->wave_data, &app->wave_length) == false) {
		printf("Could not setup audio window: %s\n", SDL_GetError());
		return;
	}
 
    app->stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
    if (!app->stream) {
        SDL_Log("Couldn't create audio stream: %s", SDL_GetError() ) ;
        return;
    }

    SDL_ResumeAudioStreamDevice(app->stream);
   
}

void pauseSound(App *app) { 
    SDL_PauseAudioStreamDevice(app->stream);
}

