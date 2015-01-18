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
	Enemy *_enemy;
	
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


private:
	Player *player;
	CooldownQueue *_cooldownqueue;

	char text [3];
	int _originBoxesX;
	int _widthBoxesX;
	const char* images[3];
	bool prepareToReturn;

	cocos2d::LabelTTF *_enemyDamageText;
	cocos2d::LabelTTF *_playerDamageText;
	cocos2d::LabelTTF *_consoleEnemyText;
	cocos2d::LabelTTF *_consolePlayerText;

	cocos2d::Sprite *_enemyhealth;
	cocos2d::Sprite *_enemyhealthBox;

	cocos2d::Sprite *_enemymana;
	cocos2d::Sprite *_enemymanaBox;
	
	cocos2d::Sprite *_enemySprite;

	cocos2d::Sprite *background_menu_sprite;
	cocos2d::Sprite *foreground_menu_sprite;

	cocos2d::Sprite *_health;
	cocos2d::Sprite *_healthBox;
	cocos2d::Sprite *_mana;
	cocos2d::Sprite *_manaBox;

	cocos2d::Sprite *attack_attributes_image [6];
	cocos2d::MenuItemImage *attack_attributes_buttons [6];
	cocos2d::Sprite *defense_attributes_image [6];
	cocos2d::MenuItemImage *defense_attributes_buttons [6];


	cocos2d::LabelTTF *_attackAttributes[6];
	cocos2d::LabelTTF *_defenseAttributes[6];

};

