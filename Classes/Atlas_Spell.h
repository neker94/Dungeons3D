#include "Spell.h"

static class Atlas_Spell
{
public:

	Spell *createSpell(int index){
		switch(index){
		case 1:
			spell.init();
			spell.setIndex(index);
			spell.setName("Bola de fuego");
			spell.setDescription("Pequeña bola de fuego. Usada por novatos");
			spell.setElementalPower(spell.FIRE, 20);
			spell.setManaCost(5);
			spell.setTime(1.6);
			break;
		case 2:
			spell.init();
			spell.setIndex(index);
			spell.setName("Erupción");
			spell.setDescription("Remueve la tierra para liberar un volcán de fuego");
			spell.setElementalPower(spell.FIRE, 50);
			spell.setManaCost(25);
			spell.setTime(2.8);
			break;
		case 3:
			spell.init();
			spell.setIndex(index);
			spell.setName("Aguijones del infierno");
			spell.setDescription("Lanza dardos envueltos en fuego negro");
			spell.setElementalPower(spell.FIRE, 15);
			spell.setElementalPower(spell.DARKNESS, 5);
			spell.setManaCost(3);
			spell.setTime(0.8);
			break;
		case 4:
			spell.init();
			spell.setIndex(index);
			spell.setName("Calcinación");
			spell.setDescription("Incinera cualquier forma de vida en los alrederores");
			spell.setElementalPower(spell.FIRE, 120);
			spell.setManaCost(70);
			spell.setTime(4.4);
			break;
		case 5:
			spell.init();
			spell.setIndex(index);
			spell.setName("Poder de Hefesto");
			spell.setDescription("Invoca al dios Hefesto para que cargue contra los enemigos");
			spell.setElementalPower(spell.FIRE, 150);
			spell.setElementalPower(spell.MAGIC, 30);
			spell.setElementalPower(spell.PHYSIC,20);
			spell.setManaCost(100);
			spell.setTime(5);
			break;
		}
	}
private:
	Spell spell;
};

