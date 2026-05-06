#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// Screen dimensions
const int SCREEN_WIDTH = 420;
const int SCREEN_HEIGHT = 500;
const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;
const int BOARD_OFFSET_X = 120;
const int BOARD_OFFSET_Y = 50;

// Board dimensions
const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;
const int CELL_SIZE = 20;

// Tetromino pieces (7 types, 4x4 grid)
const int tetromino[7][4][4] = {
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
    {{0,0,7,0},{7,7,7,0},{0,0,0,0},{0,0,0,0}}
};

// Bag system for random piece generation
int bag[7] = {0, 1, 2, 3, 4, 5, 6};
int bag_index = 0;

// Game board (0 = empty, 1-7 = filled with piece type)
int board[BOARD_HEIGHT][BOARD_WIDTH] = {0};


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
    int blocks[4][4]; // 4x4 grid for piece shape (after rotation)
} Piece;

typedef struct {
    Piece current;
    int score;
    int lines;
    int fall_timer;
    int fall_speed;
    bool game_over;
} GameState;

// next piece queue (for preview)
int next_piece_queue[5] = {0};

// holding piece
int hold_piece = -1;

// Function prototypes
bool canPlace(Piece p);
void placePiece(Piece p);
void spawnNewPiece(GameState* state);
int clearLines(void);
void rotatePieceC(Piece* p);
void rotatePieceCC(Piece* p);
void drawBoard(SDL_Renderer* renderer);
void drawPiece(SDL_Renderer* renderer, Piece p);
void hardDropPiece(GameState* state);
void shuffleBag(void); 
int getNextPiece(void);
void swapHoldPiece(GameState* state);


// Check if piece can be placed at current position
bool canPlace(Piece p) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (p.blocks[row][col] != 0) {
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
            if (p.blocks[row][col] != 0) {
                int bx = p.x + col;
                int by = p.y + row;
                
                if (by >= 0 && by < BOARD_HEIGHT && bx >= 0 && bx < BOARD_WIDTH) {
                    board[by][bx] = p.blocks[row][col];
                }
            }
        }
    }
}

// Spawn new piece at top
void spawnNewPiece(GameState* state) {
    state->current.type = next_piece_queue[0];
    // Shift queue
    for (int i = 0; i < 4; i++) {
        next_piece_queue[i] = next_piece_queue[i + 1];
    }
    next_piece_queue[4] = getNextPiece();
    state->current.x = 3;
    state->current.y = 0;
    state->current.rotation = 0;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            state->current.blocks[row][col] = tetromino[state->current.type][row][col];
        }
    }
    
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
void rotatePieceC(Piece* p) {
    Piece temp = *p;
    temp.rotation = (temp.rotation + 1) % 4;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            temp.blocks[col][3 - row] = p->blocks[row][col];
        }
    }
    
    // Try rotation
    if (!canPlace(temp)) {
        // Do nothing, keep original piece
    } else {
        *p = temp;
    }
}

void rotatePieceCC(Piece* p) {
    Piece temp = *p;
    temp.rotation = (temp.rotation + 3) % 4; // Rotate left
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            temp.blocks[3 - col][row] = p->blocks[row][col];
        }
    }
    
    // Try rotation
    if (!canPlace(temp)) {
        // Do nothing, keep original piece
    } else {
        *p = temp;
    }
}

// Draw the game board
void drawBoard(SDL_Renderer* renderer) {
    for (int row = 0; row < BOARD_HEIGHT; row++) {
        for (int col = 0; col < BOARD_WIDTH; col++) {
            SDL_Rect rect = {
                col * CELL_SIZE + BOARD_OFFSET_X,
                row * CELL_SIZE + BOARD_OFFSET_Y,
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
            if (p.blocks[row][col] != 0) {
                int x = (p.x + col) * CELL_SIZE;
                int y = (p.y + row) * CELL_SIZE;
                
                SDL_Rect rect = {x + BOARD_OFFSET_X, y + BOARD_OFFSET_Y, CELL_SIZE - 1, CELL_SIZE - 1};
                
                int color_idx = p.blocks[row][col];
                SDL_SetRenderDrawColor(renderer, colors[color_idx].r, colors[color_idx].g, colors[color_idx].b, colors[color_idx].a);
                SDL_RenderFillRect(renderer, &rect);
                
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }
}

// Hard drop piece to the lowest valid position
void hardDropPiece(GameState* state) {
    while (true) {
        state->current.y++;
        if (!canPlace(state->current)) {
            state->current.y--;
            break;
        }
    }
}

// Shuffle the bag of pieces
void shuffleBag(void) {
    for (int i = 6; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = bag[i];
        bag[i] = bag[j];
        bag[j] = temp;
    }
}

// Get next piece from bag
int getNextPiece(void) {
    if (bag_index >= 7) {
        shuffleBag();
        bag_index = 0;
    }
    return bag[bag_index++];
}

// Swap current piece with hold piece (or hold current piece if hold is empty)
void swapHoldPiece(GameState* state) {
    if (hold_piece == -1) {
        hold_piece = state->current.type;
        spawnNewPiece(state);
    } else {
        int temp = hold_piece;
        hold_piece = state->current.type;
        state->current.type = temp;
        
        // Update current piece blocks
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                state->current.blocks[row][col] = tetromino[state->current.type][row][col];
            }
        }
        
        // Reset position and rotation
        state->current.x = 3;
        state->current.y = 0;
        state->current.rotation = 0;
        
        if (!canPlace(state->current)) {
            state->game_over = true;
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

    for (int i = 0; i < 5; i++) {
        next_piece_queue[i] = getNextPiece();
    }
    
    spawnNewPiece(&state);

    bool quit = false; 
    SDL_Event e;
    const Uint8* keystate;

    printf("Tetris Game!\n");
    printf("Arrow Keys: Move, Space: Rotate, ESC: Quit\n");

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
                        hardDropPiece(&state);
                        state.fall_timer = state.fall_speed; // Force piece to lock immediately
                        break;
                    case SDLK_UP:
                    case SDLK_x:
                        rotatePieceC(&state.current);
                        break;
                    case SDLK_z:
                        rotatePieceCC(&state.current);
                        break;
                    case SDLK_LEFT:
                        state.current.x--;
                        if (!canPlace(state.current)) {
                            state.current.x++;
                        }
                        break;
                    case SDLK_RIGHT:
                        state.current.x++;
                        if (!canPlace(state.current)) {
                            state.current.x--;
                        }
                        break;
                    case SDLK_c:
                    case SDLK_LSHIFT:
                    case SDLK_RSHIFT:
                        swapHoldPiece(&state);
                        break;
                }
            }
        }

        keystate = SDL_GetKeyboardState(NULL);
        
        // Move down faster
        if (keystate[SDL_SCANCODE_DOWN]) {
            state.fall_timer += 5; // Speed up fall
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

        // Draw next piece previews
        for (int i = 0; i < 5; i++) {
            Piece preview_piece;
            preview_piece.type = next_piece_queue[i];
            preview_piece.x = BOARD_WIDTH + 1; // Preview area to the right of board
            preview_piece.y = i * 4; // Stack previews vertically
            preview_piece.rotation = 0;
            for (int row = 0; row < 4; row++) {
                for (int col = 0; col < 4; col++) {
                    preview_piece.blocks[row][col] = tetromino[preview_piece.type][row][col];
                }
            }
            drawPiece(renderer, preview_piece);
        }
        
        // Draw hold piece
        if (hold_piece != -1) {
            Piece hold_preview;
            hold_preview.type = hold_piece;
            hold_preview.x = -5; // Preview area to the left of board
            hold_preview.y = 0; // Top of preview area
            hold_preview.rotation = 0;
            for (int row = 0; row < 4; row++) {
                for (int col = 0; col < 4; col++) {
                    hold_preview.blocks[row][col] = tetromino[hold_preview.type][row][col];
                }
            }
            drawPiece(renderer, hold_preview);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(FRAME_DELAY);
    }

    if (state.game_over) {
        printf("Game Over! Score: %d, Lines: %d\n", state.score, state.lines);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
