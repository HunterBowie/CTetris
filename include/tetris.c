#include <SDL3/SDL.h>

#include "tetris.h"
#include "draw.h"
#include <time.h>
#include <stdlib.h>

int SHAPE_DATA[7][4][4][4] = {
    {{{1, 1, 0, 0},
      {1, 1, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}},
     {{1, 1, 0, 0},
      {1, 1, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}},
     {{1, 1, 0, 0},
      {1, 1, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}},
     {{1, 1, 0, 0},
      {1, 1, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}}},
    {{{0, 0, 0, 0},
      {0, 0, 0, 1},
      {0, 1, 1, 1},
      {0, 0, 0, 0}},
     {{0, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 1, 1, 0},
      {0, 0, 0, 0}},
     {{0, 0, 0, 0},
      {0, 0, 0, 0},
      {1, 1, 1, 0},
      {1, 0, 0, 0}},
     {{0, 1, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 0}}},
    {{{0, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 1, 1, 1},
      {0, 0, 0, 0}},
     {{0, 0, 0, 0},
      {0, 1, 1, 0},
      {0, 1, 0, 0},
      {0, 1, 0, 0}},
     {{0, 0, 0, 0},
      {0, 1, 1, 1},
      {0, 0, 0, 1},
      {0, 0, 0, 0}},
     {{0, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 1, 0, 0},
      {1, 1, 0, 0}}},
    {{{0, 0, 0, 0},
      {0, 1, 1, 0},
      {1, 1, 0, 0},
      {0, 0, 0, 0}},
     {{0, 1, 0, 0},
      {0, 1, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 0}},
     {{0, 0, 0, 0},
      {0, 1, 1, 0},
      {1, 1, 0, 0},
      {0, 0, 0, 0}},
     {{0, 1, 0, 0},
      {0, 1, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 0}}},
    {{{0, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 1, 0, 0}},
     {{0, 0, 0, 0},
      {1, 1, 1, 1},
      {0, 0, 0, 0},
      {0, 0, 0, 0}},
     {{0, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 1, 0, 0}},
     {{0, 0, 0, 0},
      {1, 1, 1, 1},
      {0, 0, 0, 0},
      {0, 0, 0, 0}}},
    {{{0, 0, 0, 0},
      {1, 1, 0, 0},
      {0, 1, 1, 0},
      {0, 0, 0, 0}},
     {{0, 0, 1, 0},
      {0, 1, 1, 0},
      {0, 1, 0, 0},
      {0, 0, 0, 0}},
     {{0, 0, 0, 0},
      {1, 1, 0, 0},
      {0, 1, 1, 0},
      {0, 0, 0, 0}},
     {{0, 0, 1, 0},
      {0, 1, 1, 0},
      {0, 1, 0, 0},
      {0, 0, 0, 0}}},
    {{{0, 1, 0, 0},
      {1, 1, 1, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}},
     {{0, 1, 0, 0},
      {0, 1, 1, 0},
      {0, 1, 0, 0},
      {0, 0, 0, 0}},
     {{0, 0, 0, 0},
      {1, 1, 1, 0},
      {0, 1, 0, 0},
      {0, 0, 0, 0}},
     {{0, 1, 0, 0},
      {1, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 0, 0}}}};

Color T_BLUE = {.r = 80, .g = 0, .b = 255};
Color T_RED = {.r = 255, .g = 0, .b = 60};
Color T_YELLOW = {.r = 255, .g = 230, .b = 0};
Color T_ORANGE = {.r = 255, .g = 110, .b = 0};
Color T_GREEN = {.r = 80, .g = 240, .b = 20};
Color T_PURPLE = {.r = 160, .g = 30, .b = 220};
Color T_CYAN = {.r = 0, .g = 255, .b = 255};

Color *T_COLORS[7] = {&T_YELLOW, &T_ORANGE, &T_BLUE, &T_GREEN, &T_CYAN, &T_RED, &T_PURPLE};

clock_t globalTimer = 0.0;

void _renderPiece(SDL_Renderer *renderer, int x, int y, Game *game)
{
    int row = game->piece.row;
    int col = game->piece.col;
    int initialCol = col;
    for (int shapeRow = 0; shapeRow < 4; shapeRow++)
    {
        if (row < RENDER_ROW_START)
        {
            row++;
            continue;
        }
        for (int shapeCol = 0; shapeCol < 4; shapeCol++)
        {
            if (SHAPE_DATA[game->piece.shape][game->piece.rotation][shapeRow][shapeCol])
            {

                SDL_FRect rect = {
                    .x = x + col * (game->grid.size + game->grid.margin),
                    .y = y + row * (game->grid.size + game->grid.margin),
                    .h = game->grid.size,
                    .w = game->grid.size};
                drawRect(renderer, &rect, game->piece.color, 255);
            }
            col++;
        }
        col = initialCol;
        row++;
    }
}

int _isPieceGrounded(Game *game)
{
    int row = game->piece.row;
    int col = game->piece.col;
    int initialCol = col;
    for (int shapeRow = 0; shapeRow < 4; shapeRow++)
    {
        for (int shapeCol = 0; shapeCol < 4; shapeCol++)
        {
            if (SHAPE_DATA[game->piece.shape][game->piece.rotation][shapeRow][shapeCol])
            {
                if (row > GRID_ROWS - 1)
                {
                    return 1;
                }
                if (game->grid.map[row + 1][col] != &WHITE)
                {
                    return 1;
                }
            }
            col++;
        }
        col = initialCol;
        row++;
    }
    return 0;
}

void _mapPiece(Game *game)
{
    int row = game->piece.row;
    int col = game->piece.col;
    int initialCol = col;
    for (int shapeRow = 0; shapeRow < 4; shapeRow++)
    {
        for (int shapeCol = 0; shapeCol < 4; shapeCol++)
        {
            if (SHAPE_DATA[game->piece.shape][game->piece.rotation][shapeRow][shapeCol])
            {
                game->grid.map[row][col] = game->piece.color;
            }
            col++;
        }
        col = initialCol;
        row++;
    }
}

int _isPieceAllowed(Grid *grid, Piece *piece)
{
    int row = piece->row;
    int col = piece->col;
    int initialCol = col;
    for (int shapeRow = 0; shapeRow < 4; shapeRow++)
    {
        for (int shapeCol = 0; shapeCol < 4; shapeCol++)
        {
            if (SHAPE_DATA[piece->shape][piece->rotation][shapeRow][shapeCol])
            {
                if (row > GRID_ROWS - 1)
                {
                    return 0;
                }
                if (col > GRID_COLS - 1 || col < 0)
                {
                    return 0;
                }
                if (grid->map[row][col] != &WHITE)
                {
                    return 0;
                }
            }
            col++;
        }
        col = initialCol;
        row++;
    }
    return 1;
}

Piece _getNewPiece(void)
{
    int index = rand() % 7;
    Shape shape = index;
    Color *color = T_COLORS[index];
    int col;
    if (shape == O_SHAPE || shape == I_SHAPE)
    {
        col = rand() % (GRID_COLS - 2);
    }
    else
    {
        col = rand() % (GRID_COLS - 4);
    }
    Piece piece = {.color = color, .shape = shape, .row = 0, .col = col, .rotation = 0};
    return piece;
}

int _isRowFull(Grid *grid, int row)
{
    for (int col = 0; col < GRID_COLS; col++)
    {
        if (grid->map[row][col] == &WHITE)
        {
            return 0;
        }
    }
    return 1;
}

void _shiftRows(Grid *grid, int row)
{

    for (int shiftRow = row; shiftRow > 1; shiftRow--)
    {
        for (int col = 0; col < GRID_COLS; col++)
        {
            grid->map[shiftRow][col] = grid->map[shiftRow - 1][col];
        }
    }
}

void initGame(Game *game)
{

    srand(time(0));
    rand();

    Piece piece = _getNewPiece();

    Grid grid = {.margin = 1, .size = 25, .map = {{&WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE}, {&WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE}, {&WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE}, {&WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE}, {&WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE}, {&WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE}, {&WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE}, {&WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE}, {&WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE}, {&WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE}, {&WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE}, {&WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE}, {&WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE}, {&WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE}, {&WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE}, {&WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE}, {&WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE}, {&WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE}, {&WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE}, {&WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE}, {&WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE}, {&WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE, &WHITE}}};

    Piece nextPiece = _getNewPiece();
    game->grid = grid;
    game->piece = piece;
    game->nextPiece = nextPiece;
    game->score = 0;
    game->_gTimer = clock();

    game->gameover = 0;
    game->fallingDelay = START_FALLING_DELAY;
    game->level = 1;
    game->linesCleared = 0;
}

void rotatePiece(Game *game, int amount)
{
    int previous_rot = game->piece.rotation;
    game->piece.rotation += amount;
    if (game->piece.rotation < 0)
    {
        game->piece.rotation = 3;
    }
    else if (game->piece.rotation > 3)
    {
        game->piece.rotation = 0;
    }
    if (!(_isPieceAllowed(&game->grid, &game->piece)))
    {
        game->piece.rotation = previous_rot;
    }
}

int movePiece(Game *game, int rowChange, int colChange)
{
    int move = 1;
    int row = game->piece.row;
    int col = game->piece.col;
    int initialCol = col;
    for (int shapeRow = 0; shapeRow < 4; shapeRow++)
    {
        for (int shapeCol = 0; shapeCol < 4; shapeCol++)
        {
            if (SHAPE_DATA[game->piece.shape][game->piece.rotation][shapeRow][shapeCol])
            {
                if (row + rowChange > GRID_ROWS - 1)
                {
                    move = 0;
                }
                else if (game->grid.map[row + rowChange][col] != &WHITE)
                {
                    move = 0;
                }
                if (col + colChange > GRID_COLS - 1 || col + colChange < 0)
                {
                    move = 0;
                }
                else if (game->grid.map[row][col + colChange] != &WHITE)
                {
                    move = 0;
                }
            }
            col++;
        }
        col = initialCol;
        row++;
    }
    if (move)
    {
        game->piece.col += colChange;
        game->piece.row += rowChange;
        return 1;
    }
    return 0;
}

void groundPiece(Game *game)
{
    while (movePiece(game, 1, 0))
    {
    }
}

void updateGame(Game *game)
{
    if (_isPieceGrounded(game))
    {
        if (game->piece.row == 0)
        {
            game->gameover = 1;
            return;
        }

        _mapPiece(game);
        game->piece = game->nextPiece;
        game->nextPiece = _getNewPiece();

        int linesCleared = 0;
        for (int row = 0; row < GRID_ROWS; row++)
        {
            if (_isRowFull(&game->grid, row))
            {
                _shiftRows(&game->grid, row);
                linesCleared++;
            }
        }
        if (linesCleared > 0)
        {

            switch (linesCleared)
            {
            case 1:
                game->score += 40 * game->level;
                break;

            case 2:
                game->score += 100 * game->level;
                break;

            case 3:
                game->score += 300 * game->level;
                break;

            case 4:
                game->score += 1200 * game->level;
                break;
            }
            game->linesCleared += linesCleared;
            if (game->linesCleared / LINES_PER_LEVEL > game->level - 1)
            {
                game->level += 1;
                game->fallingDelay -= FALLING_DELAY_CHANGE;
                if (game->fallingDelay < FALLING_DELAY_MIN)
                {
                    game->fallingDelay = FALLING_DELAY_MIN;
                }
                // printf("Level Up! #%d with falling delay: %f\n", game->level, game->fallingDelay);
            }
        }
    }

    if ((double)(clock() - game->_gTimer) / CLOCKS_PER_SEC > game->fallingDelay)
    {
        game->_gTimer = clock();
        game->piece.row += 1;
    }
    // if ((double) (clock() - globalTimer) / CLOCKS_PER_SEC > .5) {
    //     globalTimer = clock();
    // }
}

void renderGrid(SDL_Renderer *renderer, int x, int y, Game *game)
{
    int initialX = x;
    int initialY = y;

    Grid grid = game->grid;

    for (int row = 0; row < GRID_ROWS; row++)
    {
        if (row < RENDER_ROW_START)
        {
            y += grid.size + grid.margin;
            continue;
        }
        for (int col = 0; col < GRID_COLS; col++)
        {
            SDL_FRect rect = {.x = x, .y = y, .w = grid.size, .h = grid.size};
            drawRect(renderer, &rect, grid.map[row][col], 255);
            x += grid.size + grid.margin;
        }
        x = initialX;
        y += grid.size + grid.margin;
    }
    _renderPiece(renderer, initialX, initialY, game);
}
