#include "MainMenuScene.h"
#include "MapScene.h"
#include "Global.h"
#include <iostream>

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
	//Se obtienen las medidad de la pantalla y el origen de los elementos visibles
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//Crea el 'genereador' de eventos para el teclado. Al pulsar una tecla llama a OnKeyReleased
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(MainMenuScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this); //Pone el generador de eventos en el 'receptor' de eventos

	
	//Crea y muestra el menú
	background_menu_sprite = cocos2d::Sprite::create();
	background_menu_sprite->setTexture("menu/start_screen.png");
	background_menu_sprite->setPosition(visibleSize.width / 2 , visibleSize.height / 2); 
	this->addChild(background_menu_sprite, 0);


	//Botones del menu
	start_button = MenuItemImage::create("menu/start_button.png", "menu/start_button.png", 
		CC_CALLBACK_1(MainMenuScene::goToDungeonScene, this));
	



	auto menu = Menu::create(start_button, NULL);
	
	this->addChild(menu, 2);

    return true;
}

void MainMenuScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event){
	//Hace la accion correspondiente a la tecla pulsada
	if(keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		(this);
}

void MainMenuScene::goToDungeonScene(Ref *pSender){
	//auto scene = BattleScene::createScene();

	auto scene = MapScene::createScene();

	/*for (int i = 0; i < 3; i++)
	{
		[i] = images[i];
	}*/

	Director::getInstance()->pushScene(scene);
}


