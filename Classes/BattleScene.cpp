#include "BattleScene.h"
#include "Global.h"
#include <iostream>

USING_NS_CC;

BattleScene::BattleScene()
{
}

Scene* BattleScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	// 'layer' is an autorelease object
	auto layer = BattleScene::create();
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

bool BattleScene::init(){
	if ( !Layer::init() )
    {
        return false;
    }
	
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//player = new Player();
	//loadPlayer();
	load = true;

	_originBoxesX = 700;
	_widthBoxesX = 157;

	//Crea el 'genereador' de eventos para el teclado. Al pulsar una tecla llama a OnKeyReleased
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(BattleScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this); //Pone el generador de eventos en el 'receptor' de eventos

	//Crea y muestra el menú
	background_menu_sprite = cocos2d::Sprite::create();
	background_menu_sprite->setTexture("menu/action_menu.png");
	background_menu_sprite->setPosition(visibleSize.width / 2 , visibleSize.height / 2); 
	this->addChild(background_menu_sprite, 2);


	//Crea las imagenes de vida y cooldown del jugador
	_healthBox = cocos2d::Sprite::create("menu/health_box.png");
	_healthBox->setPosition(_originBoxesX, 585);
	this->addChild(_healthBox, 4);
	_health = cocos2d::Sprite::create("menu/health.png");
	_health->setPosition(_originBoxesX, 585);
	this->addChild(_health, 3);


	_manaBox = cocos2d::Sprite::create("menu/health_box.png");
	_manaBox->setPosition(_originBoxesX, 555);
	this->addChild(_manaBox, 4);
	_mana = cocos2d::Sprite::create("menu/mana.png");
	_mana->setPosition(_originBoxesX, 555);
	this->addChild(_mana, 3);

	//Crea las imagenes de vida y cooldown del enemigo
	_enemyhealthBox = cocos2d::Sprite::create("menu/health_box.png");
	_enemyhealthBox->setPosition(100, 585);
	this->addChild(_enemyhealthBox, 4);
	_enemyhealth = cocos2d::Sprite::create("menu/health.png");
	_enemyhealth->setPosition(100, 585);
	this->addChild(_enemyhealth, 3);


	_enemymanaBox = cocos2d::Sprite::create("menu/health_box.png");
	_enemymanaBox->setPosition(100, 555);
	this->addChild(_enemymanaBox, 4);
	_enemymana = cocos2d::Sprite::create("menu/mana.png");
	_enemymana->setPosition(100, 555);
	this->addChild(_enemymana, 3);
	

	//Crea las imágenes de los atributos de los ataques y de las defensas.
	int originX = 625, originY = 500;
	
	for(int i = 0; i < sizeof(attack_attributes_image)/sizeof(*attack_attributes_image);i++){

		attack_attributes_image[i] = cocos2d::Sprite::create();
		attack_attributes_image[i]->setTexture("menu/attack_" + std::to_string(i) + ".png");
		int displacementX = originX + attack_attributes_image[i]->getContentSize().height * 0;
		int displacementY = originY - i * (attack_attributes_image[i]->getContentSize().height + attack_attributes_image[i]->getContentSize().height/4);
		attack_attributes_image[i]->setPosition(displacementX, displacementY);

		this->addChild(attack_attributes_image[i], 3);
	}

	for(int i = 0; i < sizeof(defense_attributes_image)/sizeof(*defense_attributes_image);i++){

		defense_attributes_image[i] = cocos2d::Sprite::create();
		defense_attributes_image[i]->setTexture("menu/defense_" + std::to_string(i) + ".png");
		int displacementX = originX + defense_attributes_image[i]->getContentSize().height * 3;
		int displacementY = originY - i * (defense_attributes_image[i]->getContentSize().height + defense_attributes_image[i]->getContentSize().height/4);
		defense_attributes_image[i]->setPosition(displacementX, displacementY);

		this->addChild(defense_attributes_image[i], 3);
	}
	_enemy = new Enemy();
	Atlas_Enemy::createEnemy(_enemy, 0);
	Cooldown *c = new Cooldown();
	Cooldown *c2 = new Cooldown();
	c->init(1.0f);
	c2->init(2.0f);
	Global::player->setCooldown(c);
	_enemy->setCooldown(c2);

	//Text which display damage dealt
	_enemyDamageText = LabelTTF::create("", "Helvetica", 70, CCSizeMake(245, 100), kCCTextAlignmentCenter);
	_playerDamageText = LabelTTF::create("", "Helvetica", 70, CCSizeMake(245, 100), kCCTextAlignmentCenter);
	_enemyDamageText->setColor(Color3B::RED);
	_playerDamageText->setColor(Color3B::BLUE);
	this->addChild(_enemyDamageText, 2);
	this->addChild(_playerDamageText, 2);

	//Enemy sprite
	_enemySprite = Sprite::create(_enemy->spriteName);
	_enemySprite->setPosition(300, 300);
	this->addChild(_enemySprite, 1);

	this->scheduleUpdate();
	return true;
}

void BattleScene::update(float dt){
	
	//Actualiza la información del jugador
	float newScaleX = Global::player->getRelativeHP();
	_health->setScaleX(newScaleX);
	_health->setPositionX(_originBoxesX - ((1 - newScaleX) * _widthBoxesX ) / 2);
	newScaleX = Global::player->getCooldown()->getRelativeTime();
	_mana->setScaleX(newScaleX);
	_mana->setPositionX(_originBoxesX - ((1 - newScaleX) * _widthBoxesX ) / 2);

	//_H = player->getHp();

	//Actualiza la información del enemigo
	newScaleX = _enemy->getRelativeHP();
	_enemyhealth->setScaleX(newScaleX);
	_enemyhealth->setPositionX((_originBoxesX - 600) - ((1 - newScaleX) * _widthBoxesX ) / 2);
	newScaleX = _enemy->getCooldown()->getRelativeTime();
	_enemymana->setScaleX(newScaleX);
	_enemymana->setPositionX((_originBoxesX - 600) - ((1 - newScaleX) * _widthBoxesX ) / 2);
	
	//Actualize damage display numbers
	_enemyDamageText->setOpacity(_enemyDamageText->getOpacity()-dt*20);
	_enemyDamageText->setPositionY(_enemyDamageText->getPositionY()+dt*15);
	_playerDamageText->setOpacity(_playerDamageText->getOpacity()-dt*20);
	_playerDamageText->setPositionY(_playerDamageText->getPositionY()+dt*15);

	Global::player->getCooldown()->decreaseTime(dt);
	_enemy->getCooldown()->decreaseTime(dt);
	if(_enemy->getCooldown()->isCompleted()){
		float dmgs [6];
		int damageDealt = Global::player->getHp();
		_enemy->doDamage(_enemy->performAction(), dmgs);
		Global::player->takeDamage(dmgs);
		damageDealt-=Global::player->getHp();
		_playerDamageText->setPosition(260+rand()%80, 85+rand()%30);
		_playerDamageText->setOpacity(255);
		itoa(damageDealt, text, 10);
		_playerDamageText->setString(text);
	}
	if(Global::player->getHp() <= 0){
		Global::player->setHpCurrent(1);
		returnToMapScene(this);
	}
}
		

void BattleScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event){
	//Hace la accion correspondiente a la tecla pulsada
	
	if(keyCode == EventKeyboard::KeyCode::KEY_E)
		returnToMapScene(this);
	if(keyCode == EventKeyboard::KeyCode::KEY_Q)
		if(Global::player->getCooldown()->isCompleted()){
			float dmgs [6];
			int damageDealt = _enemy->getHp();
			Global::player->doDamage(0, dmgs);
			_enemy->takeDamage(dmgs);
			damageDealt -= _enemy->getHp();
			_enemyDamageText->setPosition(260+rand()%80, 285+rand()%30);
			_enemyDamageText->setOpacity(255);
			itoa(damageDealt, text, 10);
			_enemyDamageText->setString(text);
			if(_enemy->getHp() <= 0){
				Global::player->levelUp();
				returnToMapScene(this);
			}
		}
	if(keyCode == EventKeyboard::KeyCode::KEY_H)
		Global::player->setHpCurrent(Global::player->getHp()+(Global::player->getHpMax()-Global::player->getHp())/3+5);
}

void BattleScene::returnToMapScene(Ref *pSender){
	//savePlayer();
	load = true;
	Director::getInstance()->popScene();
}


/*void BattleScene::loadPlayer(){
	player.setHpCurrent(CCUserDefault::sharedUserDefault()->getIntegerForKey("playerHealth"));
	player.setAvailablePoints(CCUserDefault::sharedUserDefault()->getIntegerForKey("points"));


	player.setDamages(0, CCUserDefault::sharedUserDefault()->getFloatForKey("damage_0"));
	player.setDamages(1, CCUserDefault::sharedUserDefault()->getFloatForKey("damage_1"));
	player.setDamages(2, CCUserDefault::sharedUserDefault()->getFloatForKey("damage_2"));
	player.setDamages(3, CCUserDefault::sharedUserDefault()->getFloatForKey("damage_3"));
	player.setDamages(4, CCUserDefault::sharedUserDefault()->getFloatForKey("damage_4"));
	player.setDamages(5, CCUserDefault::sharedUserDefault()->getFloatForKey("damage_5"));

	player.setDefenses(0, CCUserDefault::sharedUserDefault()->getFloatForKey("defense_0"));
	player.setDefenses(1, CCUserDefault::sharedUserDefault()->getFloatForKey("defense_1"));
	player.setDefenses(2, CCUserDefault::sharedUserDefault()->getFloatForKey("defense_2"));
	player.setDefenses(3, CCUserDefault::sharedUserDefault()->getFloatForKey("defense_3"));
	player.setDefenses(4, CCUserDefault::sharedUserDefault()->getFloatForKey("defense_4"));
	player.setDefenses(5, CCUserDefault::sharedUserDefault()->getFloatForKey("defense_5"));
}

void BattleScene::savePlayer(){
	CCUserDefault::sharedUserDefault()->setIntegerForKey("playerHealth", player->getHp());
	CCUserDefault::sharedUserDefault()->setIntegerForKey("points", player->getAvailablePoints());

	CCUserDefault::sharedUserDefault()->setFloatForKey("damage_0", player->getDamages(0));
	CCUserDefault::sharedUserDefault()->setFloatForKey("damage_1", player->getDamages(1));
	CCUserDefault::sharedUserDefault()->setFloatForKey("damage_2", player->getDamages(2));
	CCUserDefault::sharedUserDefault()->setFloatForKey("damage_3", player->getDamages(3));
	CCUserDefault::sharedUserDefault()->setFloatForKey("damage_4", player->getDamages(4));
	CCUserDefault::sharedUserDefault()->setFloatForKey("damage_5", player->getDamages(5));

	CCUserDefault::sharedUserDefault()->setFloatForKey("defense_0", player->getDefenses(0));
	CCUserDefault::sharedUserDefault()->setFloatForKey("defense_1", player->getDefenses(1));
	CCUserDefault::sharedUserDefault()->setFloatForKey("defense_2", player->getDefenses(2));
	CCUserDefault::sharedUserDefault()->setFloatForKey("defense_3", player->getDefenses(3));
	CCUserDefault::sharedUserDefault()->setFloatForKey("defense_4", player->getDefenses(4));
	CCUserDefault::sharedUserDefault()->setFloatForKey("defense_5", player->getDefenses(5));
}*/