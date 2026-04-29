#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Paddle constants
const int PADDLE_WIDTH = 15;
const int PADDLE_HEIGHT = 100;
const int PADDLE_SPEED = 6;

// Ball constants
const int BALL_SIZE = 10;
const int BALL_SPEED = 5;

// Structures for game objects
typedef struct {
    float x, y;
    int width, height;
} Paddle;

typedef struct {
    float x, y;
    float vx, vy;
    int size;
} Ball;

int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    window = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialize paddles
    Paddle leftPaddle = { 20, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT };
    Paddle rightPaddle = { SCREEN_WIDTH - 20 - PADDLE_WIDTH, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT };

    // Initialize ball
    Ball ball = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, BALL_SPEED, BALL_SPEED, BALL_SIZE };

    // Main loop flag
    bool quit = false;
    SDL_Event e;
    const Uint8* keystate;

    printf("Pong Game Started!\n");
    printf("Left Paddle: W/S keys, Right Paddle: Up/Down arrows, ESC to quit\n");

    // While application is running
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                }
            }
        }

        // Get keyboard state
        keystate = SDL_GetKeyboardState(NULL);

        // Move left paddle (W/S keys)
        if (keystate[SDL_SCANCODE_W] && leftPaddle.y > 0) {
            leftPaddle.y -= PADDLE_SPEED;
        }
        if (keystate[SDL_SCANCODE_S] && leftPaddle.y + leftPaddle.height < SCREEN_HEIGHT) {
            leftPaddle.y += PADDLE_SPEED;
        }

        // Move right paddle (Up/Down arrows)
        if (keystate[SDL_SCANCODE_UP] && rightPaddle.y > 0) {
            rightPaddle.y -= PADDLE_SPEED;
        }
        if (keystate[SDL_SCANCODE_DOWN] && rightPaddle.y + rightPaddle.height < SCREEN_HEIGHT) {
            rightPaddle.y += PADDLE_SPEED;
        }

        // Move ball
        ball.x += ball.vx;
        ball.y += ball.vy;

        // Ball collision with top and bottom walls
        if (ball.y <= 0 || ball.y + ball.size >= SCREEN_HEIGHT) {
            ball.vy = -ball.vy;
            ball.y = (ball.y <= 0) ? 0 : SCREEN_HEIGHT - ball.size;
        }

        // Ball collision with left paddle
        if (ball.x <= leftPaddle.x + leftPaddle.width &&
            ball.y + ball.size >= leftPaddle.y &&
            ball.y <= leftPaddle.y + leftPaddle.height) {
            ball.vx = -ball.vx;
            ball.x = leftPaddle.x + leftPaddle.width;
        }

        // Ball collision with right paddle
        if (ball.x + ball.size >= rightPaddle.x &&
            ball.y + ball.size >= rightPaddle.y &&
            ball.y <= rightPaddle.y + rightPaddle.height) {
            ball.vx = -ball.vx;
            ball.x = rightPaddle.x - ball.size;
        }

        // Ball out of bounds - reset
        if (ball.x < 0 || ball.x > SCREEN_WIDTH) {
            ball.x = SCREEN_WIDTH / 2.0f;
            ball.y = SCREEN_HEIGHT / 2.0f;
            ball.vx = BALL_SPEED;
            ball.vy = BALL_SPEED;
        }

        // Clear screen (to black)
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        // Draw center line
        SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);
        for (int y = 0; y < SCREEN_HEIGHT; y += 10) {
            SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2, y, SCREEN_WIDTH / 2, y + 5);
        }

        // Draw paddles (white)
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_Rect leftPaddleRect = { (int)leftPaddle.x, (int)leftPaddle.y, leftPaddle.width, leftPaddle.height };
        SDL_Rect rightPaddleRect = { (int)rightPaddle.x, (int)rightPaddle.y, rightPaddle.width, rightPaddle.height };
        SDL_RenderFillRect(renderer, &leftPaddleRect);
        SDL_RenderFillRect(renderer, &rightPaddleRect);

        // Draw ball (white)
        SDL_Rect ballRect = { (int)ball.x, (int)ball.y, ball.size, ball.size };
        SDL_RenderFillRect(renderer, &ballRect);

        // Update screen
        SDL_RenderPresent(renderer);

        // Small delay to prevent high CPU usage
        SDL_Delay(16);
    }

    // Destroy renderer & window and quit SDL subsystems
    printf("Cleaning up and exiting...\n");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    SDL_Quit();

    return 0;
}