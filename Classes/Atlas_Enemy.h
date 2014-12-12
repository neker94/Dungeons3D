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
			enemy->spriteName = "enemies/red_slime.png";

			damages[0] = 1; damages[1] = 1; damages[2] = 1;
			damages[3] = 1; damages[4] = 1; damages[5] = 1;

			defenses[0] = 70; defenses[1] = 5; defenses[2] = 10;
			defenses[3] = 10; defenses[4] = 5; defenses[5] = 50;

			for (int i = 0; i < 6; i++)
			{
				enemy->setDamages(i, damages[i]);
				enemy->setDefenses(i, defenses[i]);
			}
			enemy->setHpMax(100);
			enemy->setHpCurrent(enemy->getHpMax());
			c->init(3.0f);
			enemy->setCooldown(c);
		}
	}
};

