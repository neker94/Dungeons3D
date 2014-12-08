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
}

void BattleScene::returnToMapScene(Ref *pSender){
	Director::getInstance()->popScene();
}