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

	_originBoxesX = 700;
	_widthBoxesX = 157;
	//playerPrueba = new Player();

	//Crea el 'genereador' de eventos para el teclado. Al pulsar una tecla llama a OnKeyReleased
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(BattleScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this); //Pone el generador de eventos en el 'receptor' de eventos

	//Crea y muestra el menú
	background_menu_sprite = cocos2d::Sprite::create();
	background_menu_sprite->setTexture("menu/action_menu.png");
	background_menu_sprite->setPosition(visibleSize.width / 2 , visibleSize.height / 2); 
	this->addChild(background_menu_sprite, 1);


	//Crea las imagenes de vida y cooldown del jugador
	_healthBox = cocos2d::Sprite::create("menu/health_box.png");
	_healthBox->setPosition(_originBoxesX, 585);
	this->addChild(_healthBox, 3);
	_health = cocos2d::Sprite::create("menu/health.png");
	_health->setPosition(_originBoxesX, 585);
	this->addChild(_health, 2);


	_manaBox = cocos2d::Sprite::create("menu/health_box.png");
	_manaBox->setPosition(_originBoxesX, 555);
	this->addChild(_manaBox, 3);
	_mana = cocos2d::Sprite::create("menu/mana.png");
	_mana->setPosition(_originBoxesX, 555);
	this->addChild(_mana, 2);
	

	//Crea las imágenes de los atributos de los ataques y de las defensas.
	int originX = 625, originY = 500;
	
	for(int i = 0; i < sizeof(attack_attributes_image)/sizeof(*attack_attributes_image);i++){

		attack_attributes_image[i] = cocos2d::Sprite::create();
		attack_attributes_image[i]->setTexture("menu/attack_" + std::to_string(i) + ".png");
		int displacementX = originX + attack_attributes_image[i]->getContentSize().height * 0;
		int displacementY = originY - i * (attack_attributes_image[i]->getContentSize().height + attack_attributes_image[i]->getContentSize().height/4);
		attack_attributes_image[i]->setPosition(displacementX, displacementY);

		this->addChild(attack_attributes_image[i], 2);
	}

	for(int i = 0; i < sizeof(defense_attributes_image)/sizeof(*defense_attributes_image);i++){

		defense_attributes_image[i] = cocos2d::Sprite::create();
		defense_attributes_image[i]->setTexture("menu/defense_" + std::to_string(i) + ".png");
		int displacementX = originX + defense_attributes_image[i]->getContentSize().height * 3;
		int displacementY = originY - i * (defense_attributes_image[i]->getContentSize().height + defense_attributes_image[i]->getContentSize().height/4);
		defense_attributes_image[i]->setPosition(displacementX, displacementY);

		this->addChild(defense_attributes_image[i], 2);
	}

	this->scheduleUpdate();

	return true;
}

void BattleScene::update(float dt){
	playerPrueba.update(dt);

	float newScaleX = ((float)playerPrueba.getCurrentHP())/((float)playerPrueba.getMaxHP());

	_health->setScaleX(newScaleX);

	_health->setPositionX(_originBoxesX - ((1 - newScaleX) * _widthBoxesX ) / 2);

	newScaleX = ((float)playerPrueba.getCurrentM())/((float)playerPrueba.getMaxM());

	_mana->setScaleX(newScaleX);

	_mana->setPositionX(_originBoxesX - ((1 - newScaleX) * _widthBoxesX ) / 2);
}

void BattleScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event){
	//Hace la accion correspondiente a la tecla pulsada
	
	if(keyCode == EventKeyboard::KeyCode::KEY_Q)
		returnToMapScene(this);

}

void BattleScene::returnToMapScene(Ref *pSender){
	Director::getInstance()->popScene();
}