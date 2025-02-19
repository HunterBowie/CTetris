#ifndef DRAW_GUARD
#define DRAW_GUARD


typedef struct Color {
    int r;
    int g;
    int b;
}Color;

Color BLUE;
Color GREEN;
Color RED;
Color WHITE;
Color BLACK;

Color* COLORS[5];

void drawFill(SDL_Renderer *renderer, Color *color);
void drawRect(SDL_Renderer *renderer, SDL_FRect *rect, Color *color, int alpha);
void drawLine(SDL_Renderer *renderer, int startX, int startY, int endX, int endY, int thickness, Color *color, int alpha);
void drawCircle(SDL_Renderer *renderer, int centreX, int centreY, int radius, Color *color, int alpha);
void drawPoint(SDL_Renderer *renderer, int x, int y, Color *color, int alpha);

#endif