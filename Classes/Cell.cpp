#include "Cell.h"

Cell::Cell()
{
	exits = 0;
	object_index = 0;
	isExit = false;
}

void Cell::setExits(int exit){
	exits = exit;
}

void Cell::setAsExit(){
	isExit = true;
}

void Cell::setObject(int obj_index){
	object_index = obj_index;
}

int Cell::getExits(){
	return exits;
}
