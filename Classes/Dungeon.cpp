#include "Dungeon.h"


Dungeon::Dungeon()
{
}

void Dungeon::init(){
	
	int aux [20*20] = 
	   {0, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 2, 2, 3, 2, 2, 4, 2, 2, 3, 2, 2, 3, 2, 2, 2, 2, 2, 1, 5,
		0, 0, 0, 2, 0, 0, 1, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
		0, 5, 1, 2, 0, 0, 5, 0, 0, 2, 2, 0, 2, 0, 0, 0, 5, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 4, 2, 2, 0, 1, 0, 0, 0,
		0, 0, 0, 2, 2, 3, 2, 2, 1, 5, 0, 0, 2, 0, 2, 2, 4, 2, 2, 0,
		0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 2, 0,
		0, 0, 0, 5, 0, 2, 2, 2, 0, 5, 1, 2, 4, 2, 2, 2, 4, 2, 2, 0,
		0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0,
		0, 5, 1, 2, 2, 3, 2, 4, 2, 2, 2, 0, 2, 0, 0, 0, 2, 0, 0, 0,
		0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 3, 2, 4, 2, 2, 3, 3, 2, 2, 2,
		0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 2, 0, 2, 0, 0, 2, 0, 0, 0, 1,
		0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 1, 0, 3, 2, 2, 4, 2, 2, 0, 5,
		0, 0, 0, 0, 0, 3, 2, 3, 2, 1, 5, 1, 3, 0, 0, 2, 0, 2, 0, 0,
		0, 5, 1, 2, 2, 3, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 1, 0, 0,
		0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 2, 2, 3, 0, 0, 2, 0, 5, 0, 0,
		0, 0, 0, 0, 0, 1, 0, 5, 1, 2, 0, 0, 2, 2, 2, 3, 2, 0, 0, 0,
		0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 5, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	
	for(int i = 0; i < 400; i++){
		board[i] = aux[i];
	}

	endX = 10;
	endY = 2;
	
}

bool Dungeon::canMove(){
	if(board[player->getX()+player->getY()*20+player->getDirection()] > 0
		&& board[player->getX()+player->getY()*20+player->getDirection()] < 5){
		return true;
	}
	return false;
}

bool Dungeon::playerEnds(){
	return (player->getX() == endX && player->getY() == endY)? true : false;
}

int Dungeon::distance(){
	int X = endX - player->getX();
	int Y = endY - player->getY();

	float d = sqrt((float)X * X + Y * Y);
	return (int) d;
}

void Dungeon::setPlayer(Player *p){
	player = p;
}

void Dungeon::imagesToShow(const char *output [3]){
	int tmp_X = player->getX();
	int tmp_Y = player->getY();
	for(int i = 0; i < 3; i++){
		output[i] = getImage(tmp_X, tmp_Y, player->getDirection());
		switch (player->getDirection()){
		case Direction::NORTH:
			tmp_Y--;
			break;
		case Direction::SOUTH:
			tmp_Y++;
			break;
		case Direction::EAST:
			tmp_X++;
			break;
		case Direction::WEST:
			tmp_X--;
			break;
		}
	}
}

const char *Dungeon::getImage(int cell_X, int cell_Y, int view_dir){
	int cell = cell_Y*20 + cell_X + view_dir;
	if(cell >= 400 || cell < 0)
		return "0.png";
	switch(board[cell]){
	case 0:
		return "0.png";
	case 1:
		return "1.png";
	case 2:
		if(board[cell + view_dir] != 0){
			return "2_F.png";
		}
		else{
			if(board[cell+turnLeft(view_dir)] != 0){
				return "2_L.png";
			}
			else{
				return "2_R.png"; 
			}
		}
	case 3:
		if(board[cell + view_dir] == 0){
			return "3_T.png";
		}
		else{
			if(board[cell+turnLeft(view_dir)] != 0){
				return "3_L.png";
			}
			else{
				return "3_R.png";
			}
		}
	case 4:
		return "4.png";
	}
	return "1_W.png";
}

int Dungeon::turnLeft(int view_dir){
	if(view_dir == Direction::NORTH)
		return Direction::WEST;
	if(view_dir == Direction::WEST)
		return Direction::SOUTH;
	if(view_dir == Direction::SOUTH)
		return Direction::EAST;
	return Direction::NORTH;
}

