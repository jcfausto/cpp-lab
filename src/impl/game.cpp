/*
 * game.cpp
 *
 *  Created on: 8 de jun de 2017
 *      Author: jcfausto
 *
 *  This class holds all information for our main game loop
 */

#include <SDL2/SDL.h>
#include "game.h"
#include "graphics.h"
#include "input.h"
#include "globals.h"

namespace {
	const int FPS = 50;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Game::~Game() {

}

//Every frame this method will be executed
void Game::gameLoop() {
	Graphics graphics;
	Input input;
	SDL_Event event; //Will handle events

	this->player_ = AnimatedSprite(graphics, "content/sprites/MyChar.png", 0, 0, 16, 16, 100, 100, 100);
	this->player_.setupAnimations();

	this->player_.playAnimation(globals::ANIMATION_RUN_RIGHT);

	int LAST_UPDATE_TIME = SDL_GetTicks();
	//Start the game loop
	while(true) {
		input.beginNewFrame(); //Reset the key maps

		if (SDL_PollEvent(&event)) {

			switch (event.type) {
				case SDL_KEYDOWN: {
					if (event.key.repeat == 0) {
						input.keyDownEvent(event);
					}
					break;
				}
				case SDL_KEYUP: {
					input.keyUpEvent(event);
					break;
				}
				case SDL_QUIT: {
					return;
				}
				default: {
					break;
				}
			}

		}

		//Will close the window if user hits ESCAPE
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
			return;
		}

		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME; //Stores how long this current frame took
		this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		this->draw(graphics);
	}
}

void Game::draw(Graphics &graphics) {
	graphics.clear();

	this->player_.draw(graphics, 100, 100);

	graphics.flip();
}

void Game::update(float elapsedTime) {
	this->player_.update(elapsedTime);
}