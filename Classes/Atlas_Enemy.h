#include "Enemy.h"

static class Atlas_Enemy
{
public:

	Enemy *createEnemy(int index){
		Enemy enemy;
		int damages [6];
		int defenses[6];
		switch(index){
		case 0:
			enemy.setTypeOfEnemy(enemy.FIGHTER);
			enemy.setKindoOfAction(enemy.SILLY);
			damages[0] = 70; damages[1] = 5; damages[2] = 10;
			damages[3] = 10; damages[4] = 5; damages[5] = 50;
			enemy.setDamages(damages);
		}
};

