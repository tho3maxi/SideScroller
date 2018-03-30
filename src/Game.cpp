#include <iostream>
#include "Game.h"
#include "GameObject.h"

using namespace std;

GameObject* player;

// Initializes the game class (what happens upon creation)
Game::Game() {}

// Uninitializes the game class (what happens upon deletion)
Game::~Game() {}

// Initializes the game
void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
    this->width = width;
    this->height = height;
    this->fullscreen = fullscreen;

    // Sets the flag to fullscreen mode
    int flags = 0;
    if(fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;

    // Sets up the window and opens it
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        cout << "Subsystems initialized!" << endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window) {
            cout << "Window created!" << endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            cout << "Renderer created!" << endl;
        }

        cnt = (width / 2 - 100) * 20;
        isRunning = true;
    } else
        isRunning = false;

    player = new GameObject("assets/player.png", renderer, 0, 0);

}

// Handles the user input
void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;

        case SDL_KEYDOWN:
            // These are the keyboard presses
            cout << SDL_GetKeyName( event.key.keysym.sym ) << endl;
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    isRunning = false;
                    break;
                case SDLK_LEFT:
                    printf("LEFT\n");
                    break;
                case SDLK_RIGHT:
                    printf("RIGHT\n");
                    break;
                case SDLK_UP:
                    printf("UP\n");
                    break;
                case SDLK_DOWN:
                    printf("DOWN\n");
                    break;
            }
            break;

        default:
            break;
    }
}

// This is what happens every frame
void Game::update() {
    player->Update();
}

// This is what get's rendered every frame
void Game::render() {
    SDL_RenderClear(renderer);

    // add here stuff to render
    player->Render();

    SDL_RenderPresent(renderer);
}

// Cleans the game and stops the program
void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "Game cleaned" << endl;
}