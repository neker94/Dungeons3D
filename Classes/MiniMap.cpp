#include "MiniMap.h"


MiniMap::MiniMap()
{
}

void MiniMap::init(){
	for(int i = 0; i < 400; i++)
	{
		cellsRevealed[i] = false;
	}
	//Start position revealed
	revealCell(3,4);
}

void MiniMap::revealCell(int cordX, int cordY){
	cellsRevealed[cordX + cordY * 20] = true;
}

void MiniMap::cellsRevealedNerby(int cordX, int cordY){
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			if(inMap(cordX+i-3, cordY+j-3) && cellsRevealed[(cordX+i-3) + (cordY+j-3)*20]){
				nerby[i + (j*SIZE)] = true;
			}
			else{
				nerby[i + (j*SIZE)] = false;
			}
		}
	}
}

bool MiniMap::inMap(int cordX, int cordY){
	if(cordX < 0 || cordX >= 20)
		return false;
	if(cordY < 0 || cordY >= 20)
		return false;
	return true;
}