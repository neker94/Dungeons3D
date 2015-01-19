#include "MapScene.h"
#include "GameOverScene.h"
#include <iostream>

USING_NS_CC;

Scene* MapScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = MapScene::create();
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MapScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    

	//Se obtienen las medidad de la pantalla y el origen de los elementos visibles
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Variable temporal que redimensiona las imagenes hasta que las reduzcamos a 600x600. Inicializa la cantidad de pasos dados
	float reduction = 0.5825242718446602f;
	steps = 0;
	_originBoxesX = 700;
	_widthBoxesX = 157;

	//Crea el 'genereador' de eventos para el teclado. Al pulsar una tecla llama a OnKeyReleased
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(MapScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this); //Pone el generador de eventos en el 'receptor' de eventos

	//Inicializa la mazmorra y le asigna un puntero al Jugador
	dungeon.init();
	player = new Player();
	savePlayer();
	dungeon.setPlayer(player);
	CCUserDefault::sharedUserDefault()->setBoolForKey("loadPlayer", false);
	load = false;


	//Inicializa el Minimapa
	minimap;
	minimap.init();
	
	//
	//Calcula y Crea la imagenes que representan la mazmorra. Aqui se les aplican la posicion y el escalado permanente
	//

	//Guarda en un array los Strings con la ruta de la imagen a mostrar
	dungeon.imagesToShow(images);

	//Inicializa la imagen más pequeña	
	auto aux1 = cocos2d::Sprite::create();
	s2 = aux1;
	s2->setTexture(images[2]);
    //s2->setScale(0.4f*0.4f*reduction);
	s2->setScale(0.4f*reduction);
	s2->setPosition(Vec2(visibleSize.width/2 + origin.x - 180*reduction, visibleSize.height/2/* + origin.y + 180*reduction*/));
    
	//Inicializa la imagen mediana
	aux1 = cocos2d::Sprite::create();
	s1 = aux1;
	s1->setTexture(images[1]);
    //s1->setScale(0.4f*reduction);
	s1->setScale(reduction);
	s1->setPosition(Vec2(visibleSize.width/2 + origin.x - 180*reduction, visibleSize.height/2/* + origin.y + 180*reduction*/));
    
	//Inicializa la imagen más grande
	aux1 = cocos2d::Sprite::create();
	s0 = aux1;
	//s0->setScale(reduction);
	s0->setTexture(images[0]);
	s0->setPosition(Vec2(visibleSize.width/2 + origin.x - 180*reduction, visibleSize.height/2/* + origin.y + 180*reduction*/));
	
	//Añade las tres imagenes a la Escena actual
	this->addChild(s2, 0);
	this->addChild(s1, 0);
	this->addChild(s0, 0);

	//Crea y situa los elementos del minimapa
    auto aux = cocos2d::Sprite::create("square.png");
	int tempX = 0;
	int tempY = 0;
	for(int i = 0; i < minimap.SIZE*minimap.SIZE; i++){
		minimap_images[i] = aux;
		aux = cocos2d::Sprite::create("square.png");
		minimap_images[i]->setPosition(Vec2(615 + tempX, 289 + tempY));
		this->addChild(minimap_images[i], 2);
		tempX += 30;
		if(tempX >= minimap.SIZE*30){
			tempX = 0;
			tempY -= 30;
		}
	}

	
	//Crea e inicializa la celda del minimapa donde esta el Jugador
	player_square = cocos2d::Sprite::create();
	player_square->setTexture("square_player.png");
	player_square->setPosition(Vec2(615+90, 289-90));
	this->addChild(player_square, 2);

	
	//Crea y muestra el menú
	background_menu_sprite = cocos2d::Sprite::create();
	background_menu_sprite->setTexture("menu/background_menu.png");
	background_menu_sprite->setPosition(visibleSize.width / 2 , visibleSize.height / 2); 
	this->addChild(background_menu_sprite, 1);

	foreground_menu_sprite = cocos2d::Sprite::create();
	foreground_menu_sprite->setTexture("menu/foreground_menu.png");
	foreground_menu_sprite->setPosition(visibleSize.width / 2 , visibleSize.height / 2); 
	this->addChild(foreground_menu_sprite, 3);

	//Botones del menu
	up_button = MenuItemImage::create("menu/up_button.png", "menu/up_button.png", CC_CALLBACK_0(MapScene::move, this));
	down_button = MenuItemImage::create("menu/down_button.png", "menu/down_button.png", CC_CALLBACK_0(MapScene::rotateHalf, this));
	left_button = MenuItemImage::create("menu/left_button.png", "menu/left_button.png", CC_CALLBACK_0(MapScene::rotateLeft, this));
	right_button = MenuItemImage::create("menu/right_button.png", "menu/right_button.png", CC_CALLBACK_0(MapScene::rotateRight, this));

	up_button_p = MenuItemImage::create("menu/up_button_p.png", "menu/up_button_p.png", CC_CALLBACK_0(MapScene::move, this));
	down_button_p = MenuItemImage::create("menu/down_button_p.png", "menu/down_button_p.png", CC_CALLBACK_0(MapScene::rotateHalf, this));
	left_button_p = MenuItemImage::create("menu/left_button.png", "menu/left_button.png", CC_CALLBACK_0(MapScene::rotateLeft, this));
	right_button_p = MenuItemImage::create("menu/right_button.png", "menu/right_button.png", CC_CALLBACK_0(MapScene::rotateRight, this));
	
	//Crea las imagenes de vida y cooldown del jugador
	_healthBox = cocos2d::Sprite::create("menu/health_box.png");
	_healthBox->setPosition(700, 585);
	this->addChild(_healthBox, 3);
	_health = cocos2d::Sprite::create("menu/health.png");
	_health->setPosition(700, 585);
	this->addChild(_health, 2);


	_manaBox = cocos2d::Sprite::create("menu/health_box.png");
	_manaBox->setPosition(700, 555);
	this->addChild(_manaBox, 3);
	_mana = cocos2d::Sprite::create("menu/mana.png");
	_mana->setPosition(700, 555);
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

	
	originX = visibleSize.width / 2 - (800 - 625) + 30;

	originY = visibleSize.height / 2 - 100;

	int row = 0;
	attack_attributes_buttons[0] = MenuItemImage::create("menu/attribute_button.png", "menu/attribute_button.png", CC_CALLBACK_0(MapScene::addPhisicalDamagePoint, this));
	attack_attributes_buttons[0]->setPosition(originX + 25, originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	_attackAttributes[0] = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_attackAttributes[0]->setColor(Color3B::WHITE);
	_attackAttributes[0]->setPosition(480 + originX + 30, 262 + originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	this->addChild(_attackAttributes[0], 3);
	row++;
	attack_attributes_buttons[1] = MenuItemImage::create("menu/attribute_button.png", "menu/attribute_button.png", CC_CALLBACK_0(MapScene::addFireDamagePoint, this));
	attack_attributes_buttons[1]->setPosition(originX + 25, originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	_attackAttributes[1] = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_attackAttributes[1]->setColor(Color3B::WHITE);
	_attackAttributes[1]->setPosition(480 + originX + 30, 262 + originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	this->addChild(_attackAttributes[1], 3);
	row++;
	attack_attributes_buttons[2] = MenuItemImage::create("menu/attribute_button.png", "menu/attribute_button.png", CC_CALLBACK_0(MapScene::addWaterDamagePoint, this));
	attack_attributes_buttons[2]->setPosition(originX + 25, originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	_attackAttributes[2] = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_attackAttributes[2]->setColor(Color3B::WHITE);
	_attackAttributes[2]->setPosition(480 + originX + 30, 262 + originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	this->addChild(_attackAttributes[2], 3);
	row++;
	attack_attributes_buttons[3] = MenuItemImage::create("menu/attribute_button.png", "menu/attribute_button.png", CC_CALLBACK_0(MapScene::addLightningDamagePoint, this));
	attack_attributes_buttons[3]->setPosition(originX + 25, originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	_attackAttributes[3] = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_attackAttributes[3]->setColor(Color3B::WHITE);
	_attackAttributes[3]->setPosition(480 + originX + 30, 262 + originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	this->addChild(_attackAttributes[3], 3);
	row++;
	attack_attributes_buttons[4] = MenuItemImage::create("menu/attribute_button.png", "menu/attribute_button.png", CC_CALLBACK_0(MapScene::addLightDamagePoint, this));
	attack_attributes_buttons[4]->setPosition(originX + 25, originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	_attackAttributes[4] = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_attackAttributes[4]->setColor(Color3B::WHITE);
	_attackAttributes[4]->setPosition(480 + originX + 30, 262 + originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	this->addChild(_attackAttributes[4], 3);
	row++;
	attack_attributes_buttons[5] = MenuItemImage::create("menu/attribute_button.png", "menu/attribute_button.png", CC_CALLBACK_0(MapScene::addDarkDamagePoint, this));
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
	defense_attributes_buttons[0] = MenuItemImage::create("menu/attribute_button.png", "menu/attribute_button.png", CC_CALLBACK_0(MapScene::addPhisicalDefensePoint, this));
	defense_attributes_buttons[0]->setPosition(originX + 25, originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	_defenseAttributes[0] = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_defenseAttributes[0]->setColor(Color3B::WHITE);
	_defenseAttributes[0]->setPosition(480 + originX + 30, 262 + originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	this->addChild(_defenseAttributes[0], 3);
	row++;
	defense_attributes_buttons[1] = MenuItemImage::create("menu/attribute_button.png", "menu/attribute_button.png", CC_CALLBACK_0(MapScene::addFireDefensePoint, this));
	defense_attributes_buttons[1]->setPosition(originX + 25, originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	_defenseAttributes[1] = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_defenseAttributes[1]->setColor(Color3B::WHITE);
	_defenseAttributes[1]->setPosition(480 + originX + 30, 262 + originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	this->addChild(_defenseAttributes[1], 3);
	row++;
	defense_attributes_buttons[2] = MenuItemImage::create("menu/attribute_button.png", "menu/attribute_button.png", CC_CALLBACK_0(MapScene::addWaterDefensePoint, this));
	defense_attributes_buttons[2]->setPosition(originX + 25, originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	_defenseAttributes[2] = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_defenseAttributes[2]->setColor(Color3B::WHITE);
	_defenseAttributes[2]->setPosition(480 + originX + 30, 262 + originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	this->addChild(_defenseAttributes[2], 3);
	row++;
	defense_attributes_buttons[3] = MenuItemImage::create("menu/attribute_button.png", "menu/attribute_button.png", CC_CALLBACK_0(MapScene::addLightningDefensePoint, this));
	defense_attributes_buttons[3]->setPosition(originX + 25, originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	_defenseAttributes[3] = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_defenseAttributes[3]->setColor(Color3B::WHITE);
	_defenseAttributes[3]->setPosition(480 + originX + 30, 262 + originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	this->addChild(_defenseAttributes[3], 3);
	row++;
	defense_attributes_buttons[4] = MenuItemImage::create("menu/attribute_button.png", "menu/attribute_button.png", CC_CALLBACK_0(MapScene::addLightDefensePoint, this));
	defense_attributes_buttons[4]->setPosition(originX + 25, originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	_defenseAttributes[4] = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_defenseAttributes[4]->setColor(Color3B::WHITE);
	_defenseAttributes[4]->setPosition(480 + originX + 30, 262 + originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	this->addChild(_defenseAttributes[4], 3);
	row++;
	defense_attributes_buttons[5] = MenuItemImage::create("menu/attribute_button.png", "menu/attribute_button.png", CC_CALLBACK_0(MapScene::addDarkDefensePoint, this));
	defense_attributes_buttons[5]->setPosition(originX + 25, originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	_defenseAttributes[5] = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_defenseAttributes[5]->setColor(Color3B::WHITE);
	_defenseAttributes[5]->setPosition(480 + originX + 30, 262 + originY - row * (attack_attributes_image[0]->getContentSize().height + attack_attributes_image[0]->getContentSize().height/4));
	this->addChild(_defenseAttributes[5], 3);

	auto menu = Menu::create(up_button, down_button, left_button, right_button, up_button_p, down_button_p, left_button_p, right_button_p,
		attack_attributes_buttons[0], attack_attributes_buttons[1], attack_attributes_buttons[2], attack_attributes_buttons[3], attack_attributes_buttons[4], attack_attributes_buttons[5], 
		defense_attributes_buttons[0], defense_attributes_buttons[1], defense_attributes_buttons[2], defense_attributes_buttons[3], defense_attributes_buttons[4], defense_attributes_buttons[5],NULL);

	_playerInfo = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_playerInfo->setColor(Color3B::WHITE);
	_playerInfo->setPosition(745, 490);
	this->addChild(_playerInfo, 3);

	_endInfo = LabelTTF::create("", "Helvetica", 20, CCSizeMake(245, 100), kCCTextAlignmentLeft);
	_endInfo->setColor(Color3B::WHITE);
	_endInfo->setPosition(150, 40);
	this->addChild(_endInfo, 3);

	int displacementX = visibleSize.width/2 - visibleSize.width/8;
	int displacementY = -visibleSize.height/2 + visibleSize.width/12;
	up_button->setPosition(displacementX, displacementY);
	down_button->setPosition(displacementX, displacementY - 38);
	left_button->setPosition(displacementX - 34, displacementY - 38);
	right_button->setPosition(displacementX + 34, displacementY - 38);

	displacementX = -visibleSize.width / 2 + visibleSize.height / 2;
	displacementY = (visibleSize.height / 2 - 10) - visibleSize.height / 5;
	up_button_p->setPosition(displacementX, displacementY);
	displacementY = -(visibleSize.height / 2 - 10)+ visibleSize.height / 5;
	down_button_p->setPosition(displacementX, displacementY);
	displacementX = -visibleSize.width / 2 + 100;
	left_button_p->setPosition(displacementX, 0);
	displacementX = -visibleSize.width / 2 + 490;
	right_button_p->setPosition(displacementX, 0);
	
	this->addChild(menu, 2);
	
	this->scheduleUpdate();
    return true;
}

void MapScene::update(float dt){
	//Actualiza la información del jugador
	if (load){
		loadPlayer();
		CCUserDefault::sharedUserDefault()->setBoolForKey("loadPlayer", false);
		load = false;
	}
	load = CCUserDefault::sharedUserDefault()->getBoolForKey("loadPlayer");

	float newScaleX = player->getRelativeHP();
	_health->setScaleX(newScaleX);
	_health->setPositionX(_originBoxesX - ((1 - newScaleX) * _widthBoxesX ) / 2);
	newScaleX = player->getCooldown()->getRelativeTime();
	_mana->setScaleX(newScaleX);
	_mana->setPositionX(_originBoxesX - ((1 - newScaleX) * _widthBoxesX ) / 2);

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

	info = "";
	info.appendWithFormat("You are at %d cells from the exit.", dungeon.distance());
	_endInfo->setString(info.getCString());

	if(player->getHp() == 0){
		CCUserDefault::sharedUserDefault()->setBoolForKey("winner", false);
		goToGameOverScene(this);
	}
	if (dungeon.playerEnds()){
		CCUserDefault::sharedUserDefault()->setBoolForKey("winner", true);
		goToGameOverScene(this);
	}

}

void MapScene::rotateLeft(){
	//Modifica la direccion del jugado, la celda del minimapa del jugador y cambia las imagenes de la mazmorra a las que corresponde
	player->rotateLeft();
	player_square->setRotation(player_square->getRotation() - 90.0f);
	
	dungeon.imagesToShow(images);
	s2->setTexture(images[2]);
	s1->setTexture(images[1]);
	s0->setTexture(images[0]);
}

void MapScene::rotateRight(){
	//Modifica la direccion del jugado, la celda del minimapa del jugador y cambia las imagenes de la mazmorra a las que corresponde
	player->rotateRight();
	player_square->setRotation(player_square->getRotation() + 90.0f);
	
	dungeon.imagesToShow(images);
	s2->setTexture(images[2]);
	s1->setTexture(images[1]);
	s0->setTexture(images[0]);
}

void MapScene::rotateHalf(){
	//Modifica la direccion del jugado, la celda del minimapa del jugador y cambia las imagenes de la mazmorra a las que corresponde
	player->rotateRight();
	player->rotateRight();
	player_square->setRotation(player_square->getRotation() + 180.0f);
	
	dungeon.imagesToShow(images);
	s2->setTexture(images[2]);
	s1->setTexture(images[1]);
	s0->setTexture(images[0]);
}

void MapScene::move(){
	//Modifica la posicion del jugador, actualiza el minimapa y carga las imagenes correspondientes a la nueva posicion. Tambien comprueba si hay una batalla
	if(dungeon.canMove()){
		player->move();
		dungeon.imagesToShow(images);
		s2->setTexture(images[2]);
		s1->setTexture(images[1]);
		s0->setTexture(images[0]);
		minimap.cellsRevealedNerby(player->getX(), player->getY());
		for(int i = 0; i < minimap.SIZE*minimap.SIZE; i++){
			if(minimap.nerby[i]){
				minimap_images[i]->setTexture("square_revealed.png");
			}
			else{
				minimap_images[i]->setTexture("square.png");
			}
		}
		minimap.revealCell(player->getX(), player->getY());
	}
	//Aparicion enemigos, descomentar esto para hacer pruebas

	steps++;
	srand(timeGetTime());
	float c1 = rand()%100+1;
	float c2 = 100.0f*(1-(20.0f/(20+(steps))));
	if(c1 < c2){
		steps = 0;
		savePlayer();
		goToBattleScene(this);
	}
}


void MapScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event){
	//Hace la accion correspondiente a la tecla pulsada
	float newScaleX = player->getRelativeHP();
	_health->setScaleX(newScaleX);
	_health->setPositionX(_originBoxesX - ((1 - newScaleX) * _widthBoxesX ) / 2);
	newScaleX = player->getCooldown()->getRelativeTime();
	_mana->setScaleX(newScaleX);
	_mana->setPositionX(_originBoxesX - ((1 - newScaleX) * _widthBoxesX ) / 2);
	if(keyCode == EventKeyboard::KeyCode::KEY_W)
		move();
	if(keyCode == EventKeyboard::KeyCode::KEY_A)
		rotateLeft();
	if(keyCode == EventKeyboard::KeyCode::KEY_D)
		rotateRight();
	if(keyCode == EventKeyboard::KeyCode::KEY_S)
		rotateHalf();
}

void MapScene::goToBattleScene(Ref *pSender){
	auto scene = BattleScene::createScene();

	Director::getInstance()->pushScene(scene);
}

void MapScene::goToGameOverScene(Ref *pSender){
	auto scene = GameOverScene::createScene();
	load = true;

	Director::getInstance()->replaceScene(scene);
}

void MapScene::addPhisicalDamagePoint(){
	player->addDamagePoint(0);
	
}
void MapScene::addFireDamagePoint(){
	player->addDamagePoint(1);
}

void MapScene::addWaterDamagePoint(){
	player->addDamagePoint(2);
}

void MapScene::addLightningDamagePoint(){
	player->addDamagePoint(3);
}

void MapScene::addLightDamagePoint(){
	player->addDamagePoint(4);
}

void MapScene::addDarkDamagePoint(){
	player->addDamagePoint(5);
}

void MapScene::addPhisicalDefensePoint(){
	player->addDefensePoint(0);
}
void MapScene::addFireDefensePoint(){
	player->addDefensePoint(1);
}

void MapScene::addWaterDefensePoint(){
	player->addDefensePoint(2);
}

void MapScene::addLightningDefensePoint(){
	player->addDefensePoint(3);
}

void MapScene::addLightDefensePoint(){
	player->addDefensePoint(4);
}

void MapScene::addDarkDefensePoint(){
	player->addDefensePoint(5);
}

void MapScene::loadPlayer(){
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

void MapScene::savePlayer(){
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