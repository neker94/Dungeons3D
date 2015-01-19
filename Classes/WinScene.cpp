#include "WinScene.h"
#include "MainMenuScene.h"
#include "Global.h"
#include <iostream>

USING_NS_CC;

Scene* WinScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = WinScene::create();
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool WinScene::init()
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
	listener->onKeyReleased = CC_CALLBACK_2(WinScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this); //Pone el generador de eventos en el 'receptor' de eventos

    return true;
}

void WinScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event){
	//Hace la accion correspondiente a la tecla pulsada
	if(keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		goToMainMenu;
}

void WinScene::goToMainMenu(Ref *pSender){
	//auto scene = BattleScene::createScene();

	//auto scene = MainMenuScene::createScene();

	/*for (int i = 0; i < 3; i++)
	{
		[i] = images[i];
	}*/

	Director::getInstance()->popScene();
}


