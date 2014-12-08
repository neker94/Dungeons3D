#include "Cell.h"
#include "Player.h"
#include "Direction.h"

using namespace std;

class Dungeon //hereda de la clase juego (cuando este hecha)
{
public:
	Dungeon();
	void init();
	void imagesToShow(const char *output [3]);
	void setPlayer(Player *p);
	bool canMove();

private:
	Player *player;
	int board [20*20];
	const char *getImage(int cell_X, int cell_Y, int view_dir);
	bool inMap(int cord_X, int cord_Y);
	int turnLeft(int view_dir);
};

