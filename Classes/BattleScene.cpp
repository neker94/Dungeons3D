#include "BattleScene.h"
#include <iostream>
#include "Atlas_Spell.h"

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
	
	player = new Player();
	loadPlayer();

	_originBoxesX = 700;
	_widthBoxesX = 157;
	prepareToReturn = false;

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
	player->setCooldown(c);
	_enemy->setCooldown(c2);

	//Text which display damage dealt
	_enemyDamageText = LabelTTF::create("", "Helvetica", 70, CCSizeMake(245, 100), kCCTextAlignmentCenter);
	_playerDamageText = LabelTTF::create("", "Helvetica", 70, CCSizeMake(245, 100), kCCTextAlignmentCenter);
	_consolePlayerText = LabelTTF::create("", "Helvetica", 18, CCSizeMake(550, 50), kCCTextAlignmentLeft);
	_consoleEnemyText = LabelTTF::create("", "Helvetica", 18, CCSizeMake(550, 50), kCCTextAlignmentLeft);
	_enemyDamageText->setColor(Color3B::RED);
	_playerDamageText->setColor(Color3B::BLUE);
	_consoleEnemyText->setColor(Color3B::RED);
	_consolePlayerText->setColor(Color3B::BLUE);
	_consolePlayerText->setPosition(25, 290);
	_consoleEnemyText->setPosition(25, 290);
	this->addChild(_enemyDamageText, 2);
	this->addChild(_playerDamageText, 2);
	this->addChild(_consoleEnemyText, 2);
	this->addChild(_consolePlayerText, 2);

	originX = visibleSize.width / 2 - (800 - 625) + 30;

	originY = visibleSize.height / 2 - 100;

	int row = 0;
	attack_attributes_buttons[0] = MenuItemImage::create("menu/attribute_button.png", "menu/attribute_button.png", CC_CALLBACK_0(BattleScene::addPhisicalDamagePoint, this));
	attack_attributes_buttons[0]->setPosition(originX + 25, originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	_attackAttributes[0] = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_attackAttributes[0]->setColor(Color3B::WHITE);
	_attackAttributes[0]->setPosition(480 + originX + 30, 262 + originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	this->addChild(_attackAttributes[0], 3);
	row++;
	attack_attributes_buttons[1] = MenuItemImage::create("menu/attribute_button.png", "menu/attribute_button.png", CC_CALLBACK_0(BattleScene::addFireDamagePoint, this));
	attack_attributes_buttons[1]->setPosition(originX + 25, originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	_attackAttributes[1] = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_attackAttributes[1]->setColor(Color3B::WHITE);
	_attackAttributes[1]->setPosition(480 + originX + 30, 262 + originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	this->addChild(_attackAttributes[1], 3);
	row++;
	attack_attributes_buttons[2] = MenuItemImage::create("menu/attribute_button.png", "menu/attribute_button.png", CC_CALLBACK_0(BattleScene::addWaterDamagePoint, this));
	attack_attributes_buttons[2]->setPosition(originX + 25, originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	_attackAttributes[2] = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_attackAttributes[2]->setColor(Color3B::WHITE);
	_attackAttributes[2]->setPosition(480 + originX + 30, 262 + originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	this->addChild(_attackAttributes[2], 3);
	row++;
	attack_attributes_buttons[3] = MenuItemImage::create("menu/attribute_button.png", "menu/attribute_button.png", CC_CALLBACK_0(BattleScene::addLightningDamagePoint, this));
	attack_attributes_buttons[3]->setPosition(originX + 25, originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	_attackAttributes[3] = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_attackAttributes[3]->setColor(Color3B::WHITE);
	_attackAttributes[3]->setPosition(480 + originX + 30, 262 + originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	this->addChild(_attackAttributes[3], 3);
	row++;
	attack_attributes_buttons[4] = MenuItemImage::create("menu/attribute_button.png", "menu/attribute_button.png", CC_CALLBACK_0(BattleScene::addLightDamagePoint, this));
	attack_attributes_buttons[4]->setPosition(originX + 25, originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	_attackAttributes[4] = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_attackAttributes[4]->setColor(Color3B::WHITE);
	_attackAttributes[4]->setPosition(480 + originX + 30, 262 + originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	this->addChild(_attackAttributes[4], 3);
	row++;
	attack_attributes_buttons[5] = MenuItemImage::create("menu/attribute_button.png", "menu/attribute_button.png", CC_CALLBACK_0(BattleScene::addDarkDamagePoint, this));
	attack_attributes_buttons[5]->setPosition(originX + 25, originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	_attackAttributes[5] = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_attackAttributes[5]->setColor(Color3B::WHITE);
	_attackAttributes[5]->setPosition(480 + originX + 30, 262 + originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	this->addChild(_attackAttributes[5], 3);
	

	/*-----------------------------------------------------------------
	--------------------BOTONES ATRIBUTOS DEFENSAS--------------------
	-------------------------------------------------------------------*/

	originX += 80;

	row = 0;
	defense_attributes_buttons[0] = MenuItemImage::create("menu/attribute_button.png", "menu/attribute_button.png", CC_CALLBACK_0(BattleScene::addPhisicalDefensePoint, this));
	defense_attributes_buttons[0]->setPosition(originX + 25, originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	_defenseAttributes[0] = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_defenseAttributes[0]->setColor(Color3B::WHITE);
	_defenseAttributes[0]->setPosition(480 + originX + 30, 262 + originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	this->addChild(_defenseAttributes[0], 3);
	row++;
	defense_attributes_buttons[1] = MenuItemImage::create("menu/attribute_button.png", "menu/attribute_button.png", CC_CALLBACK_0(BattleScene::addFireDefensePoint, this));
	defense_attributes_buttons[1]->setPosition(originX + 25, originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	_defenseAttributes[1] = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_defenseAttributes[1]->setColor(Color3B::WHITE);
	_defenseAttributes[1]->setPosition(480 + originX + 30, 262 + originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	this->addChild(_defenseAttributes[1], 3);
	row++;
	defense_attributes_buttons[2] = MenuItemImage::create("menu/attribute_button.png", "menu/attribute_button.png", CC_CALLBACK_0(BattleScene::addWaterDefensePoint, this));
	defense_attributes_buttons[2]->setPosition(originX + 25, originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	_defenseAttributes[2] = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_defenseAttributes[2]->setColor(Color3B::WHITE);
	_defenseAttributes[2]->setPosition(480 + originX + 30, 262 + originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	this->addChild(_defenseAttributes[2], 3);
	row++;
	defense_attributes_buttons[3] = MenuItemImage::create("menu/attribute_button.png", "menu/attribute_button.png", CC_CALLBACK_0(BattleScene::addLightningDefensePoint, this));
	defense_attributes_buttons[3]->setPosition(originX + 25, originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	_defenseAttributes[3] = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_defenseAttributes[3]->setColor(Color3B::WHITE);
	_defenseAttributes[3]->setPosition(480 + originX + 30, 262 + originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	this->addChild(_defenseAttributes[3], 3);
	row++;
	defense_attributes_buttons[4] = MenuItemImage::create("menu/attribute_button.png", "menu/attribute_button.png", CC_CALLBACK_0(BattleScene::addLightDefensePoint, this));
	defense_attributes_buttons[4]->setPosition(originX + 25, originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	_defenseAttributes[4] = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_defenseAttributes[4]->setColor(Color3B::WHITE);
	_defenseAttributes[4]->setPosition(480 + originX + 30, 262 + originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	this->addChild(_defenseAttributes[4], 3);
	row++;
	defense_attributes_buttons[5] = MenuItemImage::create("menu/attribute_button.png", "menu/attribute_button.png", CC_CALLBACK_0(BattleScene::addDarkDefensePoint, this));
	defense_attributes_buttons[5]->setPosition(originX + 25, originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	_defenseAttributes[5] = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_defenseAttributes[5]->setColor(Color3B::WHITE);
	_defenseAttributes[5]->setPosition(480 + originX + 30, 262 + originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	this->addChild(_defenseAttributes[5], 3);
	
	_playerInfo = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentRight);
	_playerInfo->setColor(Color3B::WHITE);
	_playerInfo->setPosition(645, 490);
	this->addChild(_playerInfo, 3);

	for (int i = 0; i < 6; i++)
	{
		_attackLabels[i] = LabelTTF::create( Atlas_Spell::createSpell(i)->getName(), "Helvetica", 20, CCSizeMake(245, 20), kCCTextAlignmentLeft);
	}
	row = 0;
	originY = -20;
	originX = 330;
	_attackButtons[row] = MenuItemLabel::create(_attackLabels[row], CC_CALLBACK_0(BattleScene::ThrowSpell0, this));
	_attackButtons[row]->setPosition(originX, originY - 22 * row);
	row++;
	_attackButtons[row] = MenuItemLabel::create(_attackLabels[row], CC_CALLBACK_0(BattleScene::ThrowSpell1, this));
	_attackButtons[row]->setPosition(originX, originY - 22 * row);
	row++;
	_attackButtons[row] = MenuItemLabel::create(_attackLabels[row], CC_CALLBACK_0(BattleScene::ThrowSpell2, this));
	_attackButtons[row]->setPosition(originX, originY - 22 * row);
	row++;
	_attackButtons[row] = MenuItemLabel::create(_attackLabels[row], CC_CALLBACK_0(BattleScene::ThrowSpell3, this));
	_attackButtons[row]->setPosition(originX, originY - 22 * row);
	row++;
	_attackButtons[row] = MenuItemLabel::create(_attackLabels[row], CC_CALLBACK_0(BattleScene::ThrowSpell4, this));
	_attackButtons[row]->setPosition(originX, originY - 22 * row);
	row++;
	_attackButtons[row] = MenuItemLabel::create(_attackLabels[row], CC_CALLBACK_0(BattleScene::ThrowSpell5, this));
	_attackButtons[row]->setPosition(originX, originY - 22 * row);
	row++;
	_healLabel = LabelTTF::create("Heal", "Helvetica", 20, CCSizeMake(245, 20), kCCTextAlignmentLeft);
	_healButton = MenuItemLabel::create(_healLabel, CC_CALLBACK_0(BattleScene::Heal, this));
	_healButton->setPosition(originX, originY - 22 * row);

	auto menu = Menu::create( attack_attributes_buttons[0], attack_attributes_buttons[1], attack_attributes_buttons[2], attack_attributes_buttons[3], attack_attributes_buttons[4], attack_attributes_buttons[5], 
		defense_attributes_buttons[0], defense_attributes_buttons[1], defense_attributes_buttons[2], defense_attributes_buttons[3], defense_attributes_buttons[4], defense_attributes_buttons[5], 
		_attackButtons[0], _attackButtons[1], _attackButtons[2], _attackButtons[3], _attackButtons[4], _attackButtons[5],
		_healButton, NULL);

	this->addChild(menu, 3);
	//Enemy sprite
	_enemySprite = Sprite::create(_enemy->spriteName);
	_enemySprite->setPosition(300, 300);
	this->addChild(_enemySprite, 1);

	this->scheduleUpdate();
	return true;
}

void BattleScene::update(float dt){
	if(!prepareToReturn){
		//Actualiza la información del jugador
		float newScaleX = player->getRelativeHP();
		_health->setScaleX(newScaleX);
		_health->setPositionX(_originBoxesX - ((1 - newScaleX) * _widthBoxesX ) / 2);
		newScaleX = player->getCooldown()->getRelativeTime();
		_mana->setScaleX(newScaleX);
		_mana->setPositionX(_originBoxesX - ((1 - newScaleX) * _widthBoxesX ) / 2);

		//Actualiza la información del enemigo
		newScaleX = _enemy->getRelativeHP();
		_enemyhealth->setScaleX(newScaleX);
		_enemyhealth->setPositionX((_originBoxesX - 600) - ((1 - newScaleX) * _widthBoxesX ) / 2);
		newScaleX = _enemy->getCooldown()->getRelativeTime();
		_enemymana->setScaleX(newScaleX);
		_enemymana->setPositionX((_originBoxesX - 600) - ((1 - newScaleX) * _widthBoxesX ) / 2);
	
		

		player->getCooldown()->decreaseTime(dt);
		_enemy->getCooldown()->decreaseTime(dt);
		if(_enemy->getCooldown()->isCompleted()){
			float dmgs [6];
			int damageDealt = player->getHp();
			int spellDone = _enemy->performAction();
			_enemy->doDamage(spellDone, dmgs);
			player->takeDamage(dmgs);
			damageDealt-=player->getHp();
			_playerDamageText->setPosition(260+rand()%80, 85+rand()%30);
			_playerDamageText->setOpacity(255);
			itoa(damageDealt, text, 10);
			_playerDamageText->setString(text);
		
			String c = "";
			c.appendWithFormat("El enemigo ha usado %s y te ha quitado %d PV!", Atlas_Spell::createSpell(spellDone)->getName(),damageDealt);
			_consoleEnemyText->setPosition(280, 70);
			_consolePlayerText->setPosition(280, 30);
			_consoleEnemyText->setString(c.getCString());

			
		}
		if(player->getHp() <= 0){
			player->setHpCurrent(0);
			savePlayer();
			returnToMapScene(this);
		}
		if(_enemy->getHp() <= 0){
			player->levelUp();
			prepareToReturn = true;
		}

		
	}

	//Actualize damage display numbers
	_enemyDamageText->setOpacity(_enemyDamageText->getOpacity()-dt*20);
	_enemyDamageText->setPositionY(_enemyDamageText->getPositionY()+dt*15);
	_playerDamageText->setOpacity(_playerDamageText->getOpacity()-dt*20);
	_playerDamageText->setPositionY(_playerDamageText->getPositionY()+dt*15);

	//Actualizar puntos de atributos
	_attackAttributes[0]->setString(std::to_string((int) player->getDamages(0)));
	_attackAttributes[1]->setString(std::to_string((int) player->getDamages(1)));
	_attackAttributes[2]->setString(std::to_string((int) player->getDamages(2)));
	_attackAttributes[3]->setString(std::to_string((int) player->getDamages(3)));
	_attackAttributes[4]->setString(std::to_string((int) player->getDamages(4)));
	_attackAttributes[5]->setString(std::to_string((int) player->getDamages(5)));

	_defenseAttributes[0]->setString(std::to_string((int) player->getDefenses(0)));
	_defenseAttributes[1]->setString(std::to_string((int) player->getDefenses(1)));
	_defenseAttributes[2]->setString(std::to_string((int) player->getDefenses(2)));
	_defenseAttributes[3]->setString(std::to_string((int) player->getDefenses(3)));
	_defenseAttributes[4]->setString(std::to_string((int) player->getDefenses(4)));
	_defenseAttributes[5]->setString(std::to_string((int) player->getDefenses(5)));
	if(player->availablePoints > 0){
		for (int i = 0; i < 6; i++){
			_attackAttributes[i]->setColor(Color3B::GREEN);
			_defenseAttributes[i]->setColor(Color3B::GREEN);
		}
	}
	else{
		for (int i = 0; i < 6; i++){
			_attackAttributes[i]->setColor(Color3B::WHITE);
			_defenseAttributes[i]->setColor(Color3B::WHITE);
		}
	}
	
	String info = "";
	info.appendWithFormat("Lv: %d ExpNext: %d", player->getLevel(), player->expUntilNLvl());
	_playerInfo->setString(info.getCString());

	if(prepareToReturn){
		savePlayer();
		returnToMapScene(this);
	}
	
		
}
		

void BattleScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event){
	//Hace la accion correspondiente a la tecla pulsada
	if(keyCode == EventKeyboard::KeyCode::KEY_E)
		returnToMapScene(this);
}

void BattleScene::returnToMapScene(Ref *pSender){
	
	CCUserDefault::sharedUserDefault()->setBoolForKey("loadPlayer", true);
	Director::getInstance()->popScene();
}

void BattleScene::addPhisicalDamagePoint(){
	player->addDamagePoint(0);
	
}
void BattleScene::addFireDamagePoint(){
	player->addDamagePoint(1);
}

void BattleScene::addWaterDamagePoint(){
	player->addDamagePoint(2);
}

void BattleScene::addLightningDamagePoint(){
	player->addDamagePoint(3);
}

void BattleScene::addLightDamagePoint(){
	player->addDamagePoint(4);
}

void BattleScene::addDarkDamagePoint(){
	player->addDamagePoint(5);
}

void BattleScene::addPhisicalDefensePoint(){
	player->addDefensePoint(0);
}
void BattleScene::addFireDefensePoint(){
	player->addDefensePoint(1);
}

void BattleScene::addWaterDefensePoint(){
	player->addDefensePoint(2);
}

void BattleScene::addLightningDefensePoint(){
	player->addDefensePoint(3);
}

void BattleScene::addLightDefensePoint(){
	player->addDefensePoint(4);
}

void BattleScene::addDarkDefensePoint(){
	player->addDefensePoint(5);
}

void BattleScene::ThrowSpell0(){
	ThrowSpell(0);
}
void BattleScene::ThrowSpell1(){
	ThrowSpell(1);
}
void BattleScene::ThrowSpell2(){
	ThrowSpell(2);
}
void BattleScene::ThrowSpell3(){
	ThrowSpell(3);
}
void BattleScene::ThrowSpell4(){
	ThrowSpell(4);
}
void BattleScene::ThrowSpell5(){
	ThrowSpell(5);
}

void BattleScene::ThrowSpell(int s){
	if(player->getCooldown()->isCompleted()){
		float dmgs [6];
		int damageDealt = _enemy->getHp();
		player->doDamage(s, dmgs);
		_enemy->takeDamage(dmgs);
		damageDealt -= _enemy->getHp();
		_enemyDamageText->setPosition(260+rand()%80, 285+rand()%30);
		_enemyDamageText->setOpacity(255);
		itoa(damageDealt, text, 10);
		_enemyDamageText->setString(text);

		String c = ""; c.appendWithFormat("Has usado %s y le ha quitado %d PV al enemigo!", Atlas_Spell::createSpell(s)->getName(),damageDealt);
		_consolePlayerText->setPosition(280, 70);
		_consoleEnemyText->setPosition(280, 30);
		_consolePlayerText->setString(c.getCString());
	}
}

void BattleScene::Heal(){
	player->setHpCurrent(player->getHp()+(player->getHpMax()-player->getHp())/3+5);
}

void BattleScene::loadPlayer(){
	player->setHpCurrent(CCUserDefault::sharedUserDefault()->getIntegerForKey("playerHealth"));
	player->availablePoints = (CCUserDefault::sharedUserDefault()->getIntegerForKey("points"));
	player->setLevel(CCUserDefault::sharedUserDefault()->getIntegerForKey("level"));
	player->setExperience(CCUserDefault::sharedUserDefault()->getIntegerForKey("expPoints"));


	player->setDamages(0, CCUserDefault::sharedUserDefault()->getFloatForKey("damage_0"));
	player->setDamages(1, CCUserDefault::sharedUserDefault()->getFloatForKey("damage_1"));
	player->setDamages(2, CCUserDefault::sharedUserDefault()->getFloatForKey("damage_2"));
	player->setDamages(3, CCUserDefault::sharedUserDefault()->getFloatForKey("damage_3"));
	player->setDamages(4, CCUserDefault::sharedUserDefault()->getFloatForKey("damage_4"));
	player->setDamages(5, CCUserDefault::sharedUserDefault()->getFloatForKey("damage_5"));

	player->setDefenses(0, CCUserDefault::sharedUserDefault()->getFloatForKey("defense_0"));
	player->setDefenses(1, CCUserDefault::sharedUserDefault()->getFloatForKey("defense_1"));
	player->setDefenses(2, CCUserDefault::sharedUserDefault()->getFloatForKey("defense_2"));
	player->setDefenses(3, CCUserDefault::sharedUserDefault()->getFloatForKey("defense_3"));
	player->setDefenses(4, CCUserDefault::sharedUserDefault()->getFloatForKey("defense_4"));
	player->setDefenses(5, CCUserDefault::sharedUserDefault()->getFloatForKey("defense_5"));
}

void BattleScene::savePlayer(){
	CCUserDefault::sharedUserDefault()->setIntegerForKey("playerHealth", player->getHp());
	CCUserDefault::sharedUserDefault()->setIntegerForKey("points", player->availablePoints);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("level", player->getLevel());
	CCUserDefault::sharedUserDefault()->setIntegerForKey("expPoints", player->getExperience());


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
}