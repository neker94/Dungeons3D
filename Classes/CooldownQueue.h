#include "Cooldown.h"

class CooldownQueue
{
public:
	CooldownQueue(void);
	void init();
	void actualizeCooldowns(float timeElapsed);
	void enqueue(Cooldown *cooldown);
	Cooldown *dequeue();
private:
	int length;
	Cooldown *first;
	Cooldown *last;
};

