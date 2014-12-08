#include "CooldownQueue.h"


CooldownQueue::CooldownQueue()
{
}

void CooldownQueue::init(){
	length = 0;
	first = nullptr;
	last = nullptr;
}

void CooldownQueue::enqueue(Cooldown *cooldown){
	if(length == 0){
		first = cooldown;
		last = cooldown;
	}
	else {
		if(length == 1){
		last = cooldown;
		first->setNext(last);
		}

		else{
			last->setNext(cooldown);
			last = cooldown;
		}
	}
	length++;
}

Cooldown *CooldownQueue::dequeue(){
	if(length > 0){
		Cooldown *aux = first;
		first = first->getNext();
		length--;
		return aux;
	}
	return nullptr;
}

void CooldownQueue::actualizeCooldowns(float timeElapsed){
	Cooldown *aux = first;
	if(aux == nullptr)
		return;
	for(int i = 0; i < length; i++){
		if(aux->isActive())
			aux->decreaseTime(timeElapsed);
		if(aux->isCompleted()){
			aux = aux->getNext();
			continue;
		}
		enqueue(aux);
		aux = aux->getNext();
	}
}