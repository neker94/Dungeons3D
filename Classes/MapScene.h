#ifndef __MAP_SCENE_H__
#define __MAP_SCENE_H__

#include "Dungeon.h"
#include "cocos2d.h"
#include "MiniMap.h"

class MapScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    CREATE_FUNC(MapScene);

	void goToBattleScene(Ref *pSender);

private:
	const char *images [3];
	int steps;
	Player player;
	Dungeon dungeon;
	MiniMap minimap;
	cocos2d::Sprite *s0;
	cocos2d::Sprite *s1;
	cocos2d::Sprite *s2;
	cocos2d::Sprite *player_square;
	cocos2d::Sprite *minimap_images [49];

	/*-----MENU ELEMENTS-----*/
	cocos2d::Sprite *background_menu_sprite;
	cocos2d::Sprite *foreground_menu_sprite;

	cocos2d::MenuItemImage *up_button;
	cocos2d::MenuItemImage *down_button;
	cocos2d::MenuItemImage *left_button;
	cocos2d::MenuItemImage *right_button;

	cocos2d::MenuItemImage *up_button_p;
	cocos2d::MenuItemImage *down_button_p;
	cocos2d::MenuItemImage *left_button_p;
	cocos2d::MenuItemImage *right_button_p;

	cocos2d::Sprite *attack_attributes_image [6];
	cocos2d::Sprite *defense_attributes_image [6];

	cocos2d::Sprite *_health;
	cocos2d::Sprite *_healthBox;

	cocos2d::Sprite *_mana;
	cocos2d::Sprite *_manaBox;

	void rotateLeft();
	void rotateRight();
	void rotateHalf();
	void move();
};

#endif // __MAP_SCENE_H__
