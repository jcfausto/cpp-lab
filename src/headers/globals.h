/*
 * globals.h
 *
 *  Created on: 8 de jun de 2017
 *      Author: jcfausto
 */

#ifndef HEADERS_GLOBALS_H_
#define HEADERS_GLOBALS_H_

#include <string>

namespace globals {
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	const float SPRITE_SCALE = 2.0f;

	const std::string CONTENT_SPRITES_MYCHAR = "content/sprites/MyChar.png";
	const std::string CONTENT_SPRITES_TEXTBOX = "content/sprites/TextBox.png";
	const std::string CONTENT_SPRITES_NPCCEMET = "content/sprites/NpcCemet.png";

	const std::string CONTENT_BACKGROUNDS_BKBLUE = "content/backgrounds/bkBlue.png";

	const std::string CONTENT_TILESETS = "content/tilesets/";
	const std::string CONTENT_MAPS = "content/maps/";

	const std::string MAPS_MAP_1 = "Map1";

	const std::string ANIMATION_IDLE_LEFT = "IdleLeft";
	const std::string ANIMATION_IDLE_RIGHT = "IdleRight";
	const std::string ANIMATION_RUN_LEFT = "RunLeft";
	const std::string ANIMATION_RUN_RIGHT = "RunRight";
	const std::string ANIMATION_IDLE_LEFT_UP = "idleLeftUp";
	const std::string ANIMATION_IDLE_RIGHT_UP = "idleRightUp";
	const std::string ANIMATION_RUN_LEFT_UP = "runLeftUp";
	const std::string ANIMATION_RUN_RIGHT_UP = "runRightUp";
	const std::string ANIMATION_LOOK_DOWN_LEFT = "lookDownLeft";
	const std::string ANIMATION_LOOK_DOWN_RIGHT = "lookDownRight";
	const std::string ANIMATION_LOOK_BACKWARDS_LEFT = "lookBackwardsLeft";
	const std::string ANIMATION_LOOK_BACKWARDS_RIGHT = "lookBackwardsRight";

	//Bat aninations
	const std::string BAT_ANIMATION_FLY_LEFT = "FlyLeft";
	const std::string BAT_ANIMATION_FLY_RIGHT = "FlyRight";
	const float BAT_ANIMATION_VERTICAL_STEP = .02;
	const float BAT_ANIMATION_VERTICAL_MOVEMENT_RANGE = 30; //30 units up or down

	const int BAT_DAMAGE_VALUE = -1;

	//Each number on TextBox sprite file has 8 pixels of width
	const int SPRITE_TEXTBOX_NUMBER_PIXEL_WIDTH = 8;
	//Current health bar width is equals to 39px
	const int SPRITE_TEXTBOX_CURRENT_HEALTH_BAR_WIDTH = 39;

	const std::string UNKNOWN_FILENAME = "UNKNOWN_FILENAME";

	//Max supporter health value is 3
	const int PLAYER_MAX_HEALTH = 3;

	//Player start the game with full health
	const int PLAYER_INITIAL_HEALTH = 3;

}

namespace sides {
	enum Side {
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		NONE
	};

	const inline Side getOppositeSide(Side side) {
		return
				side == TOP ? BOTTOM :
				side == BOTTOM ? TOP :
				side == LEFT ? RIGHT :
				side == RIGHT ? LEFT :
				NONE;
	}
}

enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

struct Vector2 {
	int x, y;

	Vector2() :
		x(0), y(0)
	{}

	Vector2(int x, int y) :
		x(x), y(y)
	{}

	Vector2 zero() {
		return Vector2(0, 0);
	}
};

#endif /* HEADERS_GLOBALS_H_ */
