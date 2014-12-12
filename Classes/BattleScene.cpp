#include "BattleScene.h"
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

	//Crea el 'genereador' de eventos para el teclado. Al pulsar una tecla llama a OnKeyReleased
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(BattleScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this); //Pone el generador de eventos en el 'receptor' de eventos

	//Crea y muestra el men�
	background_menu_sprite = cocos2d::Sprite::create();
	background_menu_sprite->setTexture("menu/action_menu.png");
	background_menu_sprite->setPosition(visibleSize.width / 2 , visibleSize.height / 2); 
	this->addChild(background_menu_sprite, 2);

	_originBoxesX = 700;
	_widthBoxesX = 157;

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
	

	//Crea las im�genes de los atributos de los ataques y de las defensas.
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
	player = new Player();
	_enemy = new Enemy();
	Atlas_Enemy::createEnemy(_enemy, 0);
	Cooldown *c = new Cooldown();
	Cooldown *c2 = new Cooldown();
	c->init(1.0f);
	c2->init(2.0f);
	player->setCooldown(c);
	_enemy->setCooldown(c2);


	//Enemy sprite
	_enemySprite = Sprite::create(_enemy->spriteName);
	_enemySprite->setPosition(300, 300);
	this->addChild(_enemySprite, 1);

	this->scheduleUpdate();
	return true;
}

void BattleScene::update(float dt){

	//Actualiza la informaci�n del jugador
	float newScaleX = player->getRelativeHP();
	_health->setScaleX(newScaleX);
	_health->setPositionX(_originBoxesX - ((1 - newScaleX) * _widthBoxesX ) / 2);
	newScaleX = player->getCooldown()->getRelativeTime();
	_mana->setScaleX(newScaleX);
	_mana->setPositionX(_originBoxesX - ((1 - newScaleX) * _widthBoxesX ) / 2);

	//Actualiza la informaci�n del enemigo
	newScaleX = _enemy->getRelativeHP();
	_enemyhealth->setScaleX(newScaleX);
	_enemyhealth->setPositionX((_originBoxesX - 600) - ((1 - newScaleX) * _widthBoxesX ) / 2);
	newScaleX = _enemy->getCooldown()->getRelativeTime();
	_enemymana->setScaleX(newScaleX);
	_enemymana->setPositionX((_originBoxesX - 600) - ((1 - newScaleX) * _widthBoxesX ) / 2);
	
	player->getCooldown()->decreaseTime(dt);
	_enemy->getCooldown()->decreaseTime(dt);
	if(_enemy->getCooldown()->isCompleted()){
		//player->takeDamage(_enemy->doDamage(0));
		player->setHpCurrent(player->getHp() - 10);
		Cooldown *aux = new Cooldown();
		aux->init(2.0f);
		_enemy->setCooldown(aux);
	}
	if(player->getHp() <= 0)
		returnToMapScene(this);
}
		

void BattleScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event){
	//Hace la accion correspondiente a la tecla pulsada
	
	if(keyCode == EventKeyboard::KeyCode::KEY_E)
		returnToMapScene(this);
	if(keyCode == EventKeyboard::KeyCode::KEY_Q)
		if(player->getCooldown()->isCompleted()){
			//_enemy->takeDamage(player->doDamage(0));
			_enemy->setHpCurrent(_enemy->getHp() - 10);
			Cooldown *aux = new Cooldown();
			aux->init(1.0f);
			player->setCooldown(aux);
			if(_enemy->getHp() <= 0)
				returnToMapScene(this);
		}
}

void BattleScene::returnToMapScene(Ref *pSender){
	Director::getInstance()->popScene();
}