#include "Player.h"

Player::Player()
{
	posX = 3;
	posY = 4;
	direction = Direction::NORTH;
}

int Player::getX(){
	return posX;
}

int Player::getY(){
	return posY;
}

void Player::rotateLeft(){
	if(direction == Direction::NORTH)
		direction = Direction::WEST;
	else if(direction == Direction::WEST)
		direction = Direction::SOUTH;
	else if(direction == Direction::SOUTH)
		direction = Direction::EAST;
	else if(direction == Direction::EAST)
		direction = Direction::NORTH;
}

void Player::rotateRight(){
	rotateLeft();
	rotateLeft();
	rotateLeft();
}

void Player::move(){
	switch(direction){
	case Direction::NORTH:
		posY--;
		break;
	case Direction::WEST:
		posX--;
		break;
	case Direction::SOUTH:
		posY++;
		break;
	case Direction::EAST:
		posX++;
		break;
	}
}

int Player::getDirection(){
	return direction;
}

void Player::setDirection(int dir){
	direction = dir;
}

