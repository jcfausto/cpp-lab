/*
 * player.h
 *
 *  Created on: 10 de jun de 2017
 *      Author: jcfausto
 */

#ifndef HEADERS_PLAYER_H_
#define HEADERS_PLAYER_H_

#include "graphics.h"
#include "animatedsprite.h"
#include "globals.h"
#include "slope.h"
#include "level.h"

class Level;

class Player : public AnimatedSprite {
public:
	Player();
	virtual ~Player();
	Player(Graphics &graphics, Vector2 spawnPoint);

	void draw(Graphics &grapics);
	void update(float elapsedTime);

	virtual void animationDone(std::string currentAnimation);
	virtual void setupAnimations();


	/* MOVING FUNCTIONS */

	/* void moveLeft
	 * Moves the player left by -dx_
	 */
	void moveLeft();

	/* void moveRight
	 * Moves the player right by dx_
	 */
	void moveRight();

	/* void stopMoving
	 * Stops moving the player
	 */
	void stopMoving();

	/* void lookUp
	 * Will make Quote look up
	 */
	void lookUp();

	/* void stopLookingUp
	 * sets lookingUp_ to false
	 */
	void stopLookingUp();

	/* void lookDown
	 * Will make Quote look down
	 */
	void lookDown();

	/* void stopLookingDown
	 * sets lookingDown_ to false
	 */
	void stopLookingDown();

	/* void jump
	 * Start jumping
	 */
	void jump();

	void handleTileCollisions(std::vector<Rectangle> &other);
	void handleSlopeCollisions(std::vector<Slope> &other);

	/* void handleDoorCollision
	 * Handle player's collision with a particular door
	 */
	void handleDoorCollision(std::vector<Door> &other, Level &level, Graphics &graphics);

	/* void handleEnemyCollision
	 * Handle player's collision with enemies
	 */
	void handleEnemyCollision(std::vector<Enemy*> &other);

	/* const float getX const
	 * Return x_
	 */
	const float getX() const;

	/* const float getY const
	 * Return y_
	 */
	const float getY() const;

	const inline int getMaxHealth() const { return this->maxHealth_; }
	const inline int getCurrentHealth() const { return this->currentHealth_; }

	void gainHealth(int amount);

private:
	//Delta of the change in the x and y positions.
	float dx_, dy_;

	//Current player's facing direction
	Direction facing_;

	/* bool grounded_
	 * True if standing in ground or false if the Player is in the air
	 */
	bool grounded_;

	/* bool lookingUp_
	 * True if the player is looking up
	 */
	bool lookingUp_;

	/* bool lookingDown_
	 * True if the player is looking down
	 */
	bool lookingDown_;

	/* int maxHealth_
	 * Represents the health limit
	 */
	int maxHealth_;

	/* int currentHealth_
	 * Represents current health value
	 */
	int currentHealth_;
};


#endif /* HEADERS_PLAYER_H_ */
