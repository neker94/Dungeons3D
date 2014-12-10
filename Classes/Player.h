#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Direction.h"
#include "Character.h"

class Player:Character
{
public:
	Player();
	void Player::update(float dt);
	void move();
	void rotateLeft();
	void rotateRight();
	int getX();
	int getY();
	int getDirection();
	void setDirection(int dir);
	int getCurrentHP();
	int getMaxHP();
	int getCurrentM();
	int getMaxM();
private:
	int posX;
	int posY;
	int direction;
};

#endif