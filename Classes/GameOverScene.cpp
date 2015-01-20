#include "GameOverScene.h"
#include "MapScene.h"
#include "Global.h"
#include <iostream>

USING_NS_CC;

Scene* GameOverScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
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
	listener->onKeyReleased = CC_CALLBACK_2(GameOverScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this); //Pone el generador de eventos en el 'receptor' de eventos

	if(CCUserDefault::sharedUserDefault()->getBoolForKey("winner"))
		_gameOverText = LabelTTF::create("CONGRATULATIONS\nYOU WIN!", "Helvetica", 30, CCSizeMake(300, 100), kCCTextAlignmentCenter);
	else
		_gameOverText = LabelTTF::create("YOU LOSE...", "Helvetica", 30, CCSizeMake(300, 100), kCCTextAlignmentCenter);

	_gameOverText->setPosition(visibleSize.width/2, visibleSize.height/2);
	this->addChild(_gameOverText);

	_restartLabel = LabelTTF::create("RESTART", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentCenter);
	_restartButton = MenuItemLabel::create(_restartLabel, CC_CALLBACK_1(GameOverScene::restart, this));
	_restartButton->setPosition(0, -100);

	_returnLabel = LabelTTF::create("MAIN MENU", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentCenter);
	_returnButton = MenuItemLabel::create(_returnLabel, CC_CALLBACK_1(GameOverScene::goToMainMenu, this));
	_returnButton->setPosition(0, -130);

	auto menu = Menu::create(_restartButton, _returnButton, NULL);
	this->addChild(menu);

    return true;
}

void GameOverScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event){
	//Hace la accion correspondiente a la tecla pulsada
	if(keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		goToMainMenu(this);
	if(keyCode == EventKeyboard::KeyCode::KEY_Q)
		restart(this);
}

void GameOverScene::goToMainMenu(Ref *pSender){
	//auto scene = BattleScene::createScene();

	//auto scene = MainMenuScene::createScene();

	/*for (int i = 0; i < 3; i++)
	{
		[i] = images[i];
	}*/

	Director::getInstance()->popScene();
}

void GameOverScene::restart(Ref *pSender){
	auto scene = MapScene::createScene();

	Director::getInstance()->replaceScene(scene);
}

