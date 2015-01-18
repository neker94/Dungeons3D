#ifndef __MAP_SCENE_H__
#define __MAP_SCENE_H__

#include "Dungeon.h"
#include "cocos2d.h"
#include "MiniMap.h"
#include "BattleScene.h"
#include "Player.h"

class MapScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    CREATE_FUNC(MapScene);
	void update(float dt);

	void addPhisicalDamagePoint();
	void addFireDamagePoint();
	void addWaterDamagePoint();
	void addLightningDamagePoint();
	void addLightDamagePoint();
	void addDarkDamagePoint();

	void addPhisicalDefensePoint();
	void addFireDefensePoint();
	void addWaterDefensePoint();
	void addLightningDefensePoint();
	void addLightDefensePoint();
	void addDarkDefensePoint();


	void goToBattleScene(Ref *pSender);

private:
	Player *player;
	const char *images [3];
	int steps;
	Dungeon dungeon;
	MiniMap minimap;
	bool load;

	void savePlayer();
	void loadPlayer();

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
	cocos2d::MenuItemImage *attack_attributes_buttons [6];
	cocos2d::Sprite *defense_attributes_image [6];
	cocos2d::MenuItemImage *defense_attributes_buttons [6];

	
	cocos2d::LabelTTF *_attackAttributes[6];
	cocos2d::LabelTTF *_defenseAttributes[6];
	char text [3];

	void rotateLeft();
	void rotateRight();
	void rotateHalf();
	void move();
};

#endif // __MAP_SCENE_H__
