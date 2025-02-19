#include <SDL3/SDL.h>

#ifndef APP_GUARD
#define APP_GUARD

typedef struct App
{
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_AudioStream *stream;
    Uint8 *wave_data;
    Uint32 wave_length;
} App;

int initApp(App *app, char caption[], int width, int height);
void destroyApp(App *app);
void playSound(App *app, char filePath[]);
void pauseSound(App *app);

#endif