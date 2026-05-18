// session3_template.c
// Starting point for Tetris project.
// Assumes SDL2 is initialized, a window and renderer are created,
// and a basic game loop is running.

#include <SDL.h>
#include <stdio.h>   // For printf error messages
#include <stdbool.h> // For bool type
#include <stdlib.h>
#include <time.h>

// --- Game Constants ---
// Screen dimensions
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 740

// Tetris Board dimensions (in terms of blocks)
#define BLOCK_SIZE 30
#define COLUMNS 10
#define ROWS 20
#define BLOCK_FALL_INTERVAL 500

// Calculated board dimensions in pixels (useful for drawing board boundaries)
const int BOARD_DRAW_WIDTH = COLUMNS * BLOCK_SIZE;
const int BOARD_DRAW_HEIGHT = ROWS * BLOCK_SIZE;

// Offset to draw the board (e.g., to center it or place UI next to it)
const int BOARD_OFFSET_X = 50; // Example: Start board 50px from left
const int BOARD_OFFSET_Y = 50; // Example: Start board 50px from top

// --- Global SDL Variables ---
SDL_Window* window = NULL;     // The window we'll be rendering to
SDL_Renderer* renderer = NULL; // The renderer for the window
const SDL_Color colors[8] = {
    {50, 50, 50, 255},       // blank
    {0, 255, 255, 255},   // I
    {0, 0, 255, 255},     // J
    {255, 128, 0, 255},   // L
    {255, 255, 0, 255},   // O
    {0, 255, 0, 255},     // S
    {255, 0, 255, 255},   // T
    {255, 0, 0, 255},     // Z
};

// --- Variables for Tetris logic --- 
// The main game board: a 2D array representing the grid.
// Each cell stores whether it's EMPTY (0) or FILLED (1).
int board[ROWS][COLUMNS]; // Will be initialized in this project.


// *** Project #1: Define different types and shapes of each Tetromino block *** 
// Hint: You can use 4D arrays "int shapes[7][4][4][4]" to represent 7 types of tetromino block, each with 4 different shapes, 4 x 4 blocks.
// Below code includes shape representation of 'I' Tetromino block.
const int shapes[7][4][4][4] = {
    // I
    {{{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
     {{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}},
     {{0,0,0,0},{0,0,0,0},{1,1,1,1},{0,0,0,0}},
     {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}}},
    // J
    {{{1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
     {{0,1,1,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}},
     {{0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0}},
     {{0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}}},
    // L
    {{{0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
     {{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}},
     {{0,0,0,0},{1,1,1,0},{1,0,0,0},{0,0,0,0}},
     {{1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}}},
    // O
    {{{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
     {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
     {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
     {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}}},
    // S
    {{{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
     {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},
     {{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}},
     {{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}}},
    // T
    {{{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
     {{0,1,0,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
     {{0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}},
     {{0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}}},
    // Z
    {{{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
     {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
     {{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}},
     {{0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}}},
    };

// Global variables to store the state of the currently falling Tetromino piece
// These variables logically describe the current Tetromino piece.
int currentPieceX;        // X-coordinate on the board (in block units)
int currentPieceY;        // Y-coordinate on the board (in block units)
int currentPieceType;     // Index (0-6) for the shape type from the 'shapes' array
int currentPieceRotation; // Index (0-3) for the current rotation


// --- Function Declarations ---
bool InitializeSDL(); // Sets up SDL, window, and renderer
void CloseSDL();      // Cleans up SDL resources
void DrawBlock(int pixelX, int pixelY, SDL_Color color); // Helper function to draw current piece.
void InitializeGame(); // Initialize the game (board, current block)
void DrawCurrentPiece(); // Function to draw the current Tetromino piece on the board.
void DrawBoard(); // Function to draw the board.
bool CheckCollision(int newX, int newY, int pType, int pRotation); // true if collides
void LockPiece(); // lock on the board
// void SpawnNewPiece(); // spawn new piece. (collision not checked)

// --- Main Function ---
int main(int argc, char* args[]) {
    // Start up SDL and create window/renderer
    if (!InitializeSDL()) {
        printf("Failed to initialize SDL!\n");
        // CloseSDL(); // Ensure cleanup even on partial init failure
        return 1; // Indicate an error
    }

    InitializeGame(); // Initialize the game (board, current block)

    // Main loop flag
    bool running = true;

    // Event handler
    SDL_Event e;




    // Game loop
    while (running) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit (e.g., clicks the X button)
            if (e.type == SDL_QUIT) {
                running = false;
            }
            // User presses a key
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE: // Quit on Escape key
                        running = false;
                        break;
                        // Other key handling will be added in later sessions
                }
            }
        }

        // --- Game Logic Updates would go here in later sessions ---

        static int last_fall_time = 0;
        if (SDL_GetTicks() - last_fall_time > BLOCK_FALL_INTERVAL) {
            if (!CheckCollision(currentPieceX, currentPieceY + 1, currentPieceType, currentPieceRotation)) {
                currentPieceY++;
            } else {
                LockPiece();
                currentPieceX = 3;
                currentPieceY = 0;
                currentPieceRotation = rand() % 4;
                currentPieceType = rand() % 7;
                // SpawnNewPiece();
                running = !CheckCollision(currentPieceX, currentPieceY, currentPieceType, currentPieceRotation);
            }
            last_fall_time = SDL_GetTicks();
        }


        // --- Drawing ---
        // 1. Clear the screen (to a background color)
        //    Set draw color (arguments are R, G, B, Alpha)
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); // Dark gray background
        SDL_RenderClear(renderer); // Fill the entire screen with the current draw color

        // 2. Draw the game board area (as a simple rectangle for now)
        SDL_Rect boardRect = {
            BOARD_OFFSET_X,          // X position
            BOARD_OFFSET_Y,          // Y position
            BOARD_DRAW_WIDTH,        // Width
            BOARD_DRAW_HEIGHT        // Height
        };
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black for the board playable area
        SDL_RenderFillRect(renderer, &boardRect);

        // (Optional) Draw a border around the board
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Lighter gray for border
        SDL_RenderDrawRect(renderer, &boardRect);

        // 3. Draw the current Tetromino piece using its global state variables
        DrawBoard();
        DrawCurrentPiece();

        // 4. Update the screen with what we've drawn
        SDL_RenderPresent(renderer);

        // Frame rate cap (optional, to prevent using 100% CPU)
        SDL_Delay(1000 / 60); // Aim for roughly 60 FPS
    }

    // Free resources and close SDL
    CloseSDL();

    return 0;
}

// --- Function Implementations ---
bool InitializeSDL() {
    // Initialize SDL video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Create window
    window = SDL_CreateWindow(
        "SKKU Tetris", // Window title
        SDL_WINDOWPOS_UNDEFINED,         // Initial x position
        SDL_WINDOWPOS_UNDEFINED,         // Initial y position
        SCREEN_WIDTH,                    // Width, in pixels
        SCREEN_HEIGHT,                   // Height, in pixels
        SDL_WINDOW_SHOWN                 // Flags
    );

    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit(); // Cleanup SDL initialization
        return false;
    }

    // Create renderer for window
    // Using -1 for index to initialize the first one supporting the requested flags
    // SDL_RENDERER_ACCELERATED uses hardware acceleration
    // SDL_RENDERER_PRESENTVSYNC synchronizes rendering with the refresh rate
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window); // Cleanup window
        SDL_Quit();               // Cleanup SDL initialization
        return false;
    }

    // If everything initialized successfully
    printf("SDL Initialized Successfully!\n");
    return true;
}

void CloseSDL() {
    // Destroy renderer
    if (renderer) { // Check if it was actually created
        SDL_DestroyRenderer(renderer);
        renderer = NULL; // Set to NULL to prevent double deletion
        printf("Renderer destroyed.\n");
    }

    // Destroy window
    if (window) { // Check if it was actually created
        SDL_DestroyWindow(window);
        window = NULL; // Set to NULL
        printf("Window destroyed.\n");
    }

    // Quit SDL subsystems
    SDL_Quit();
    printf("SDL quit.\n");
}

void InitializeGame() {
    // To-do: Initialize the game board to be empty (0).
    // Hint: Game board is essentially 2D array with ROWS and COLUMNS.
    // Hint: int board[ROWS][COLUMNS];
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            board[row][col] = 0;
        }
    }

    // To-do: Initialize the first tetromino block using the global variables defined earlier.
    srand(time(NULL));
    currentPieceX = 3;
    currentPieceY = 0;
    currentPieceRotation = rand() % 4;
    currentPieceType = rand() % 7;
    // SpawnNewPiece();


    printf("Game Initialized. Current piece type: %d at board coordinates (%d, %d), rotation: %d\n",
        currentPieceType, currentPieceX, currentPieceY, currentPieceRotation);
}

void DrawCurrentPiece() {
    // Function to draw the current Tetromino piece on the board.

    // To-do: Calculate which block in the board[ROWS][COLUMNS] should be filled based on the "shapes[7][4][4][4]" array 
    // and the global variables currentPieceX, currentPieceY, currentPieceType, and currentPeiceRotation 
    // that you initialized in InitalizeGame() function.
    int tetrominos[4][2]; // [row, col]
    int num = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shapes[currentPieceType][currentPieceRotation][i][j] == 1) {
                tetrominos[num][0] = i + currentPieceY;
                tetrominos[num++][1] = j + currentPieceX;
            }
        }
    }

    //  To-do: Calculate the actual pixel position of the block using BOARD_OFFSET and BLOCK_SIZE.
    // the pixel position of the block [X][Y] is [BOARD_OFFSET_X + X*BLOCK_SIZE][BOARD_OFFSET_Y + Y*BLOCK_SIZE]
    int tetromino_pixels[4][2]; // [x, y]
    for (int i = 0; i < 4; i++) {
        tetromino_pixels[i][0] = tetrominos[i][1] * BLOCK_SIZE + BOARD_OFFSET_X;
        tetromino_pixels[i][1] = tetrominos[i][0] * BLOCK_SIZE + BOARD_OFFSET_Y;
    }

    // To-do: Use DrawBlock function below to draw a block starting at (pixelX, pixelY) pixel coordinate.
    for (int i = 0; i < 4; i++) {
        DrawBlock(tetromino_pixels[i][0], tetromino_pixels[i][1], colors[currentPieceType + 1]);
    }
}

void DrawBlock(int pixelX, int pixelY, SDL_Color color) {
    // Set the color for the piece. For now, let's use a single color (e.g., Red).
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); // Bright Red (R, G, B, Alpha)

    // Define the rectangle for a single block on the screen
    SDL_Rect blockRect = {
        pixelX + 1, 
        pixelY + 1, 
        BLOCK_SIZE - 2, // Width of the block (slightly smaller for a grid line effect)
        BLOCK_SIZE - 2  // Height of the block (slightly smaller for a grid line effect)
    };

    // Draw the filled rectangle for this block
    SDL_RenderFillRect(renderer, &blockRect);
}

void DrawBoard() {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            int pixelX = BOARD_OFFSET_X + col * BLOCK_SIZE;
            int pixelY = BOARD_OFFSET_Y + row * BLOCK_SIZE;
            DrawBlock(pixelX, pixelY, colors[board[row][col]]);
        }
    }
}

bool CheckCollision(int newX, int newY, int pType, int pRotation) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shapes[pType][pRotation][i][j] == 1) {
                int boardX = newX + j;
                int boardY = newY + i;
                if (boardX < 0 || boardX >= COLUMNS || boardY < 0 || boardY >= ROWS) return true;
                if (board[boardY][boardX] > 0) return true;
            }
        }
    }
    return false;
}

void LockPiece() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shapes[currentPieceType][currentPieceRotation][i][j] == 1) {
                int boardX = currentPieceX + j;
                int boardY = currentPieceY + i;
                board[boardY][boardX] = currentPieceType + 1;
            }
        }
    }
}

// void SpawnNewPiece() {
//     static int bag[7] = {0, 1, 2, 3, 4, 5, 6};
//     static int bag_index = 7;

//     if (bag_index >= 7) {
//         for (int i = 6; i > 0; i--) {
//             int j = rand() % (i + 1);
//             int temp = bag[i];
//             bag[i] = bag[j];
//             bag[j] = temp;
//         }
//         bag_index = 0;
//     }

//     currentPieceX = 3;
//     currentPieceY = 0;
//     currentPieceRotation = 0;
//     currentPieceType = bag[bag_index++];
// }





