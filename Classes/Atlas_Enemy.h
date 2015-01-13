#include "Character.h"
#include "Cooldown.h"

class Atlas_Enemy
{
public:

	static void createEnemy(Enemy *enemy, int index){
		float damages [6];
		float defenses[6];
		switch(index){
		case 0:
			//Sets image
			enemy->spriteName = "enemies/red_slime.png";
			//Sets its damages
			damages[0] = 30; damages[1] = 5; damages[2] = 20;
			damages[3] = 5; damages[4] = 5; damages[5] = 5;
			//Sets its defenses
			defenses[0] = 50; defenses[1] = 5; defenses[2] = 15;
			defenses[3] = 10; defenses[4] = 5; defenses[5] = 50;
			//Adds the spells the enmy can do
			enemy->addSpell(0); enemy->addSpell(3);
			//Stores the damages and the defenses in enemy
			for (int i = 0; i < 6; i++)
			{
				enemy->setDamages(i, damages[i]);
				enemy->setDefenses(i, defenses[i]);
			}
			//Sets the experience point given by the enemy when defeated
			enemy->exp = 10;
			//Sets the hp points
			enemy->setHpMax(60);
			enemy->setHpCurrent(enemy->getHpMax());
			//Starts the cooldown for battle start (always 3 secs)
			enemy->getCooldown()->init(3.0f);
		}
	}
};

