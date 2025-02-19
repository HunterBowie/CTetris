#include <SDL3/SDL.h>

#include <stdio.h>
#include "draw.h"

Color BLUE = {.r = 0, .g = 0, .b = 255};
Color GREEN = {.r = 0, .g = 255, .b = 0};
Color RED = {.r = 255, .g = 0, .b = 0};
Color WHITE = {.r = 255, .g = 255, .b = 255};
Color BLACK = {.r = 0, .g = 0, .b = 0};

Color* COLORS[5] = {&BLUE, &GREEN, &RED, &WHITE, &BLACK};


void drawFill(SDL_Renderer *renderer, Color *color) {
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);
    SDL_RenderClear(renderer);
}

void drawRect(SDL_Renderer *renderer, SDL_FRect *rect, Color *color, int alpha) {
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, alpha);
    SDL_RenderFillRect(renderer, rect);
}

void drawLine(SDL_Renderer *renderer, int startX, int startY, int endX, int endY, int thickness, Color *color, int alpha) {
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, alpha);
    SDL_RenderLine(renderer, startX, startY, endX, endY);
    if (thickness > 1) {
        int xOffset = 1;
        int yOffset = 1;
        while (thickness > 1) {
            SDL_RenderLine(renderer, startX+xOffset, startY+yOffset, endX+xOffset, endY+yOffset);
            SDL_RenderLine(renderer, startX-xOffset, startY-yOffset, endX-xOffset, endY-yOffset);
            thickness--;
            xOffset++;
            yOffset++;
        }
    }
    

}

void drawCircle(SDL_Renderer *renderer, int centreX, int centreY, int radius, Color *color, int alpha)  {

    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, alpha);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderPoint(renderer, centreX + dx, centreY + dy);
            }
        }
    }

}
void drawPoint(SDL_Renderer *renderer, int x, int y, Color *color, int alpha) {
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, alpha);
    SDL_RenderPoint(renderer, x, y);
}





