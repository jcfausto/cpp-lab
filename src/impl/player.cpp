/*
 * player.cpp
 *
 *  Created on: 10 de jun de 2017
 *      Author: jcfausto
 */

#include "player.h"
#include "graphics.h"
#include "globals.h"

namespace player_constants {
	const float WALK_SPEED = 0.2f;
	const float JUMP_SPEED = 0.7f;

	//Gravity related constants
	const float GRAVITY = 0.002f;
	const float GRAVITY_CAP = 0.8f;

}

Player::Player(){}
Player::~Player() {}

Player::Player(Graphics &graphics, Vector2 spawnPoing) :
	AnimatedSprite(graphics, globals::CONTENT_SPRITES_MYCHAR, 0, 0, 16, 16, spawnPoing.x, spawnPoing.y, 100),
	dx_(0),
	dy_(0),
	facing_(RIGHT),
	grounded_(false),
	lookingUp_(false),
	lookingDown_(false),
	maxHealth_(globals::PLAYER_MAX_HEALTH),
	currentHealth_(globals::PLAYER_INITIAL_HEALTH)
{
	graphics.loadImage(globals::CONTENT_SPRITES_MYCHAR);
	this->setupAnimations();
	this->playAnimation(globals::ANIMATION_RUN_RIGHT);
}

void Player::setupAnimations() {
	this->addAnimation(1, 0, 0, globals::ANIMATION_IDLE_LEFT, 16, 16, Vector2(0,0));
	this->addAnimation(1, 0, 16, globals::ANIMATION_IDLE_RIGHT, 16, 16, Vector2(0,0));
	this->addAnimation(3, 0, 0, globals::ANIMATION_RUN_LEFT, 16, 16, Vector2(0,0));
	this->addAnimation(3, 0, 16, globals::ANIMATION_RUN_RIGHT, 16, 16, Vector2(0,0));
	this->addAnimation(1, 3, 0, globals::ANIMATION_IDLE_LEFT_UP, 16, 16, Vector2(0,0));
	this->addAnimation(1, 3, 16, globals::ANIMATION_IDLE_RIGHT_UP, 16, 16, Vector2(0,0));
	this->addAnimation(3, 3, 0, globals::ANIMATION_RUN_LEFT_UP, 16, 16, Vector2(0,0));
	this->addAnimation(3, 3, 16, globals::ANIMATION_RUN_RIGHT_UP, 16, 16, Vector2(0,0));
	this->addAnimation(1, 6, 0, globals::ANIMATION_LOOK_DOWN_LEFT, 16, 16, Vector2(0,0));
	this->addAnimation(1, 6, 16, globals::ANIMATION_LOOK_DOWN_RIGHT, 16, 16, Vector2(0,0));
	this->addAnimation(1, 7, 0, globals::ANIMATION_LOOK_BACKWARDS_LEFT, 16, 16, Vector2(0,0));
	this->addAnimation(1, 7, 16, globals::ANIMATION_LOOK_BACKWARDS_RIGHT, 16, 16, Vector2(0,0));
}


void Player::draw(Graphics &graphics) {
	AnimatedSprite::draw(graphics, this->x_, this->y_);
}

/* MOVING FUNCTIONS */

void Player::moveLeft() {
	if (this->lookingDown_ == true && this->grounded_ == true) {
		return;
	}

	this->dx_ = -player_constants::WALK_SPEED;

	if (this->lookingUp_ == false) {
		this->playAnimation(globals::ANIMATION_RUN_LEFT);
	}

	this->facing_ = LEFT;
}

void Player::moveRight() {
	//TODO: Code duplication here. Look at MoveLeft.
	if (this->lookingDown_ == true && this->grounded_ == true) {
		return;
	}

	this->dx_ = player_constants::WALK_SPEED;

	if (this->lookingUp_ == false) {
		this->playAnimation(globals::ANIMATION_RUN_RIGHT);
	}

	this->facing_ = RIGHT;
}

void Player::stopMoving() {
	this->dx_ = 0; //Don't want to move.

	if (this->lookingUp_ == false && this->lookingDown_ == false) {
		this->playAnimation(this->facing_ == LEFT ? globals::ANIMATION_IDLE_LEFT : globals::ANIMATION_IDLE_RIGHT);
	}

}

void Player::lookUp() {
	this->lookingUp_ = true;
	if (this->dx_ == 0) { //Not moving
		this->playAnimation(this->facing_ == RIGHT ? globals::ANIMATION_IDLE_RIGHT_UP : globals::ANIMATION_IDLE_LEFT_UP );
	} else { //Moving
		this->playAnimation(this->facing_ == RIGHT ? globals::ANIMATION_RUN_RIGHT_UP : globals::ANIMATION_RUN_LEFT_UP);
	}
}

void Player::stopLookingUp() {
	this->lookingUp_ = false;
}

void Player::lookDown() {
	this->lookingDown_ = true;
	if (this->grounded_ == true) {
		//We need to interact (turn backwards)
		this->playAnimation(this->facing_ == RIGHT ? globals::ANIMATION_LOOK_BACKWARDS_RIGHT : globals::ANIMATION_LOOK_BACKWARDS_LEFT);
	} else {
		this->playAnimation(this->facing_ == RIGHT ? globals::ANIMATION_LOOK_DOWN_RIGHT : globals::ANIMATION_LOOK_DOWN_LEFT);
	}
}

void Player::stopLookingDown() {
	this->lookingDown_ = false;
}

void Player::jump() {
	if (this->grounded_) {
		this->dy_ = 0;
		this->dy_ -= player_constants::JUMP_SPEED;
		this->grounded_ = false;
	}
}

void Player::animationDone(std::string currentAnimation) {}

void Player::update(float elapsedTime) {
	//Apply gravity
	if (this->dy_  <= player_constants::GRAVITY_CAP) {
		this->dy_ += player_constants::GRAVITY * elapsedTime;
	}

	//This is what actually will move the character on the screen
	//Move by dx_
	this->x_ += this->dx_ * elapsedTime;
	AnimatedSprite::update(elapsedTime);

	//Move by dy_
	this->y_ += this->dy_ * elapsedTime;
}

//Handles collisions with ALL tiles the player is colliding with
void Player::handleTileCollisions(std::vector<Rectangle> &other) {
	//Figure out which side the collision happened on and move the player accordingly
	for (int i = 0; i < other.size(); i++) {
		sides::Side collisionSide = Sprite::getCollisionSide(other.at(i));
		if (collisionSide != sides::NONE) {
			switch (collisionSide) {
			case sides::TOP:
				this->dy_ = 0;
				this->y_ = other.at(i).getBottom() + 1;

				//Stops the player when he's grounded and colliding at the top.
				if (this->grounded_) {
					this->dx_ = 0;
					this->x_ -= this->facing_ == RIGHT ? 0.5f : -0.5f;
				}
				this->y_ = other.at(i).getBottom() + 1;
				break;
			case sides::BOTTOM:
				this->y_ = other.at(i).getTop() - this->boundingBox_.getHeight() - 1;
				this->dy_ = 0;
				this->grounded_ = true;
				break;
			case sides::LEFT:
				this->x_ = other.at(i).getRight() + 1;
				break;
			case sides::RIGHT:
				this->x_ = other.at(i).getLeft() - this->boundingBox_.getWidth() - 1;
				break;
			case sides::NONE:
				break;
			}
		}
	}
}

//Handles collisions with ALL slopes the player is colliding with
void Player::handleSlopeCollisions(std::vector<Slope> &other) {
	for (int i = 0; i < other.size(); i++) {
		//Calculate where on the slope the player's bottom center is touching
		//and use y=mx+b to figure our the y position to place him at
		//First calculate "b" (slope intercept) using one of the points (b = y - mx)
		int b = (other.at(i).getP1().y - (other.at(i).getSlope() * std::fabs(other.at(i).getP1().x)));

		//Now get player's center x
		int centerX = this->boundingBox_.getCenterX();

		//Now pass that X into the equation y = mx + b (using our newly found b and x) to get the new y position
		int newY = (other.at(i).getSlope() * centerX) + b - 8; //8 is temporary to fix a problem

		//Re-position the player to the correct "y"
		if (this->grounded_) {
			this->y_ = newY - this->boundingBox_.getHeight();
			this->grounded_ = true; //TODO: Why set true if it's already true?
		}

	}
}

void Player::handleDoorCollision(std::vector<Door> &others, Level &level, Graphics &graphics) {
	//Check if the player is grounded and holding the down arrow
	//If so, go through the door. If not, do nothing
	for (int i = 0; i < others.size(); i++) {
		if (this->grounded_ == true && this->lookingDown_ == true) {
			level = Level(others.at(i).getDestination(), graphics);
			this->x_ = level.getPlayerSpawnPoint().x;
			this->y_ = level.getPlayerSpawnPoint().y;
		}
	}

}

void Player::handleEnemyCollision(std::vector<Enemy*> &others) {
	for (int i = 0; i < others.size(); i++) {
		others.at(i)->touchPlayer(this);
	}
}

void Player::gainHealth(int amount) {
	this->currentHealth_ += amount;
}

const float Player::getX() const {
	return this->x_;
}

const float Player::getY() const {
	return this->y_;
}


