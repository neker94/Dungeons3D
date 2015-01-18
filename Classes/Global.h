#ifndef GLOBAL_H // header guards
#define GLOBAL_H
#include "Player.h"
#include "cocos2d.h"

static Player *_player = new Player();
static const char* images[3];
static int _originBoxesX = 700;
static int _widthBoxesX = 157;
static cocos2d::Sprite *_health;
static cocos2d::Sprite *_healthBox;
static cocos2d::Sprite *_mana;
static cocos2d::Sprite *_manaBox;

#endif