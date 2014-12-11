#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"
#include "Character.h"
#include "CooldownQueue.h"
#include "Atlas_Enemy.h"

class BattleScene : public cocos2d::Layer
{
public:
	BattleScene();

	static cocos2d::Scene* createScene();
	virtual bool init();
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void update(float dt);
	void returnToMapScene(Ref *pSender);
	CREATE_FUNC(BattleScene);

	const char *images [3];
	Player *player;
	Enemy *_enemy;


private:
	CooldownQueue *_cooldownqueue;
	int _originBoxesX;
	int _widthBoxesX;
	cocos2d::Sprite *_health;
	cocos2d::Sprite *_healthBox;

	cocos2d::Sprite *_mana;
	cocos2d::Sprite *_manaBox;
	
	cocos2d::Sprite *_enemySprite;

	cocos2d::Sprite *background_menu_sprite;
	cocos2d::Sprite *foreground_menu_sprite;

	cocos2d::Sprite *attack_attributes_image [6];
	cocos2d::Sprite *defense_attributes_image [6];

};

