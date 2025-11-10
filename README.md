# Tetris from Scratch in C using SDL3

## About the Project

I had been using Pygame to create games in Python and I was curious how it worked to draw shapes and create a window. I learned that SDL3 is the library that Pygame uses under the hood to render things in the window so I decided to create a game with it to learn about how it works. 

<img width="391" height="611" alt="Screenshot 2025-11-10 at 11 25 25 AM" src="https://github.com/user-attachments/assets/1615f39c-b463-4bc0-aa03-8695bff688c7" />


## How to Run it

Run `make` and then `./output` or `output` (for windows) in the folder after cloning.


## Example of Streaming Sound in SDL3

```c
void playSound(App *app, char filePath[]){
	SDL_AudioSpec spec;

	if (SDL_LoadWAV(filePath, &spec, &app->wave_data, &app->wave_length) == false) {
		SDL_Log("Could not setup audio window: %s\n", SDL_GetError());
		return;
	}
 
    app->stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
    if (!app->stream) {
        SDL_Log("Couldn't create audio stream: %s", SDL_GetError() ) ;
        return;
    }

    SDL_ResumeAudioStreamDevice(app->stream);
   
}
```

