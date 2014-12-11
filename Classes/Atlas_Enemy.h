#include "Character.h"
#include "Cooldown.h"

class Atlas_Enemy
{
public:

	static void createEnemy(Enemy *enemy, int index){
		float damages [6];
		float defenses[6];
		Cooldown *c = new Cooldown();
		switch(index){
		case 0:
			damages[0] = 70; damages[1] = 5; damages[2] = 10;
			damages[3] = 10; damages[4] = 5; damages[5] = 50;
			enemy->setDamages(damages);
			enemy->setDefenses(defenses);
			enemy->setHpMax(100);
			enemy->setHpCurrent(enemy->getHpMax());
			c->init(3.0f);
			enemy->setCooldown(c);
		}
	}
};

