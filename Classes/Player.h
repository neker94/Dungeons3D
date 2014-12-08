#include "Direction.h"
#include "Character.h"

class Player:Character
{
public:
	Player();
	void move();
	void rotateLeft();
	void rotateRight();
	int getX();
	int getY();
	int getDirection();
	void setDirection(int dir);
private:
	int posX;
	int posY;
	int direction;
};

