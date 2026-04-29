#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// Screen dimensions
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 600;

// Board dimensions
const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;
const int CELL_SIZE = 20;

// Game board (0 = empty, 1-7 = filled with piece type)
int board[BOARD_HEIGHT][BOARD_WIDTH] = {0};

// Tetromino pieces (7 types, 4x4 grid)
int tetromino[7][4][4] = {
    // I piece (cyan)
    {{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
    // O piece (yellow)
    {{2,2,0,0},{2,2,0,0},{0,0,0,0},{0,0,0,0}},
    // T piece (purple)
    {{0,3,0,0},{3,3,3,0},{0,0,0,0},{0,0,0,0}},
    // S piece (green)
    {{0,4,4,0},{4,4,0,0},{0,0,0,0},{0,0,0,0}},
    // Z piece (red)
    {{5,5,0,0},{0,5,5,0},{0,0,0,0},{0,0,0,0}},
    // L piece (orange)
    {{6,0,0,0},{6,6,6,0},{0,0,0,0},{0,0,0,0}},
    // J piece (blue)
    {{0,7,0,0},{7,7,7,0},{0,0,0,0},{0,0,0,0}}
};

// Color palette for pieces
SDL_Color colors[8] = {
    {0, 0, 0, 255},       // 0: Black (empty)
    {0, 240, 240, 255},   // 1: Cyan (I)
    {240, 240, 0, 255},   // 2: Yellow (O)
    {240, 0, 240, 255},   // 3: Magenta (T)
    {0, 240, 0, 255},     // 4: Green (S)
    {240, 0, 0, 255},     // 5: Red (Z)
    {240, 160, 0, 255},   // 6: Orange (L)
    {0, 0, 240, 255}      // 7: Blue (J)
};

typedef struct {
    int type;       // 0-6 for piece type
    int x, y;       // Top-left position on board
    int rotation;   // 0-3 for rotation state
} Piece;

typedef struct {
    Piece current;
    int score;
    int lines;
    int fall_timer;
    int fall_speed;
    bool game_over;
} GameState;

// Function prototypes
bool canPlace(Piece p);
void placePiece(Piece p);
void spawnNewPiece(GameState* state);
int clearLines(void);
void rotatePiece(Piece* p);
void drawBoard(SDL_Renderer* renderer);
void drawPiece(SDL_Renderer* renderer, Piece p);

// Check if piece can be placed at current position
bool canPlace(Piece p) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (tetromino[p.type][row][col] != 0) {
                int bx = p.x + col;
                int by = p.y + row;
                
                // Check bounds
                if (bx < 0 || bx >= BOARD_WIDTH || by >= BOARD_HEIGHT) {
                    return false;
                }
                
                // Check collision with board
                if (by >= 0 && board[by][bx] != 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

// Place piece permanently on board
void placePiece(Piece p) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (tetromino[p.type][row][col] != 0) {
                int bx = p.x + col;
                int by = p.y + row;
                
                if (by >= 0 && by < BOARD_HEIGHT && bx >= 0 && bx < BOARD_WIDTH) {
                    board[by][bx] = tetromino[p.type][row][col];
                }
            }
        }
    }
}

// Spawn new piece at top
void spawnNewPiece(GameState* state) {
    state->current.type = rand() % 7;
    state->current.x = 3;
    state->current.y = 0;
    state->current.rotation = 0;
    
    if (!canPlace(state->current)) {
        state->game_over = true;
    }
}

// Clear completed lines and return count
int clearLines(void) {
    int cleared = 0;
    
    for (int row = BOARD_HEIGHT - 1; row >= 0; row--) {
        bool full = true;
        for (int col = 0; col < BOARD_WIDTH; col++) {
            if (board[row][col] == 0) {
                full = false;
                break;
            }
        }
        
        if (full) {
            cleared++;
            // Shift rows down
            for (int r = row; r > 0; r--) {
                for (int c = 0; c < BOARD_WIDTH; c++) {
                    board[r][c] = board[r - 1][c];
                }
            }
            // Clear top row
            for (int c = 0; c < BOARD_WIDTH; c++) {
                board[0][c] = 0;
            }
            row++; // Check this row again
        }
    }
    
    return cleared;
}

// Rotate piece 90 degrees clockwise
void rotatePiece(Piece* p) {
    int old_rot = p->rotation;
    p->rotation = (p->rotation + 1) % 4;
    
    // Try rotation
    if (!canPlace(*p)) {
        p->rotation = old_rot; // Revert if collision
    }
}

// Draw the game board
void drawBoard(SDL_Renderer* renderer) {
    for (int row = 0; row < BOARD_HEIGHT; row++) {
        for (int col = 0; col < BOARD_WIDTH; col++) {
            SDL_Rect rect = {
                col * CELL_SIZE,
                row * CELL_SIZE,
                CELL_SIZE - 1,
                CELL_SIZE - 1
            };
            
            int cell = board[row][col];
            SDL_SetRenderDrawColor(renderer, colors[cell].r, colors[cell].g, colors[cell].b, colors[cell].a);
            SDL_RenderFillRect(renderer, &rect);
            
            // Draw grid
            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}

// Draw current falling piece
void drawPiece(SDL_Renderer* renderer, Piece p) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (tetromino[p.type][row][col] != 0) {
                int x = (p.x + col) * CELL_SIZE;
                int y = (p.y + row) * CELL_SIZE;
                
                SDL_Rect rect = {x, y, CELL_SIZE - 1, CELL_SIZE - 1};
                
                int color_idx = tetromino[p.type][row][col];
                SDL_SetRenderDrawColor(renderer, colors[color_idx].r, colors[color_idx].g, colors[color_idx].b, colors[color_idx].a);
                SDL_RenderFillRect(renderer, &rect);
                
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }
}

int main(int argc, char* args[]) {
    srand(time(NULL));
    
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    GameState state = {0};
    state.fall_speed = 30; // Frames before piece falls
    state.fall_timer = 0;
    
    spawnNewPiece(&state);

    bool quit = false;
    SDL_Event e;
    const Uint8* keystate;

    printf("Tetris Game!\n");
    printf("Arrow Keys: Move, Space: Rotate, Down: Faster fall, ESC: Quit\n");

    while (!quit && !state.game_over) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_SPACE:
                        rotatePiece(&state.current);
                        break;
                }
            }
        }

        keystate = SDL_GetKeyboardState(NULL);
        
        // Move left
        if (keystate[SDL_SCANCODE_LEFT]) {
            state.current.x--;
            if (!canPlace(state.current)) {
                state.current.x++;
            }
        }
        
        // Move right
        if (keystate[SDL_SCANCODE_RIGHT]) {
            state.current.x++;
            if (!canPlace(state.current)) {
                state.current.x--;
            }
        }
        
        // Move down faster
        if (keystate[SDL_SCANCODE_DOWN]) {
            state.fall_timer += 2;
        }

        // Gravity
        state.fall_timer++;
        if (state.fall_timer >= state.fall_speed) {
            state.fall_timer = 0;
            state.current.y++;
            
            if (!canPlace(state.current)) {
                state.current.y--; // Revert move
                placePiece(state.current);
                
                int cleared = clearLines();
                state.score += cleared * 100;
                state.lines += cleared;
                
                // Increase difficulty
                if (state.lines > 0 && state.lines % 10 == 0) {
                    state.fall_speed = (state.fall_speed > 10) ? state.fall_speed - 2 : 10;
                }
                
                spawnNewPiece(&state);
            }
        }

        // Clear and render
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawBoard(renderer);
        drawPiece(renderer, state.current);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    if (state.game_over) {
        printf("Game Over! Score: %d, Lines: %d\n", state.score, state.lines);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}