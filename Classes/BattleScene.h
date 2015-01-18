#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"
#include "Character.h"
#include "CooldownQueue.h"
#include "Atlas_Enemy.h"
#include "Global.h"

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
	Enemy *_enemy;
	Player *player;

private:
	CooldownQueue *_cooldownqueue;

	void loadPlayer();
	void savePlayer();

	char text [3];

	cocos2d::LabelTTF *_enemyDamageText;
	cocos2d::LabelTTF *_playerDamageText;

	cocos2d::Sprite *_enemyhealth;
	cocos2d::Sprite *_enemyhealthBox;

	cocos2d::Sprite *_enemymana;
	cocos2d::Sprite *_enemymanaBox;
	
	cocos2d::Sprite *_enemySprite;

	cocos2d::Sprite *background_menu_sprite;
	cocos2d::Sprite *foreground_menu_sprite;

	cocos2d::Sprite *attack_attributes_image [6];
	cocos2d::Sprite *defense_attributes_image [6];

};

