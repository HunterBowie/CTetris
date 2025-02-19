#include <stdio.h>
#include <SDL3/SDL.h>
#include "draw.h"
#include "app.h"
#include "tetris.h"

int WIDTH = 400;
int HEIGHT = 600;


int main() {
    
    App app = {};

    int error = initApp(&app, "Tetris", WIDTH, HEIGHT);
    if (error == 1) {
        return 1;
    }

    playSound(&app, "music.wav");
    
    Game game;
    initGame(&game);

    int quit = 0;
    
    while (!quit){
        if (SDL_GetAudioStreamAvailable(app.stream) < (int)app.wave_length) {
            SDL_PutAudioStreamData(app.stream, app.wave_data, app.wave_length);
        }

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    quit = 1;
                    break;
                
                case SDL_EVENT_KEY_DOWN:
                    if (event.key.scancode == SDL_SCANCODE_UP) {
                        rotatePiece(&game, 1);
                    }
                    else if (event.key.scancode == SDL_SCANCODE_DOWN) {
                        rotatePiece(&game, -1);
                    }
                    else if (event.key.scancode == SDL_SCANCODE_SPACE) {
                        groundPiece(&game);
                    }
                    if (event.key.scancode == SDL_SCANCODE_LEFT) {
                        movePiece(&game, 0, -1);
                    }
                    if (event.key.scancode == SDL_SCANCODE_RIGHT) {
                        movePiece(&game, 0, 1);
                    }
                    break;
                
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    break;
                    
                              
                default:
                    break;
            }

        }
        

        drawFill(app.renderer, &BLACK);
        updateGame(&game);
        renderGrid(app.renderer, WIDTH/2-(((game.grid.size+game.grid.margin)*GRID_COLS)/2), -25, &game);
        SDL_RenderPresent(app.renderer);


        if (game.gameover) {
            quit = 1;
            printf("\nGame Over :v\n");
            printf("score: %d\n", game.score);
            printf("level: %d\n", game.level);
            printf("lines cleared: %d\n", game.linesCleared);

        }
        
        
        
    }
    destroyApp(&app);
    
    return 0;
}

//gcc main.c -o play -I include -L lib -l SDL2-2.0.0