#include "MapScene.h"
#include "BattleScene.h"
#include "Global.h"
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

	//Crea el 'genereador' de eventos para el teclado. Al pulsar una tecla llama a OnKeyReleased
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(MapScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this); //Pone el generador de eventos en el 'receptor' de eventos

	//Inicializa la mazmorra y le asigna un puntero al Jugador
	dungeon.init();
	dungeon.setPlayer(&player);
	
	//Inicializa el Jugador

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


	auto menu = Menu::create(up_button, down_button, left_button, right_button, up_button_p, down_button_p, left_button_p, right_button_p, NULL);
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

    return true;
}

void MapScene::rotateLeft(){
	//Modifica la direccion del jugado, la celda del minimapa del jugador y cambia las imagenes de la mazmorra a las que corresponde
	player.rotateLeft();
	player_square->setRotation(player_square->getRotation() - 90.0f);
	
	dungeon.imagesToShow(images);
	s2->setTexture(images[2]);
	s1->setTexture(images[1]);
	s0->setTexture(images[0]);
}

void MapScene::rotateRight(){
	//Modifica la direccion del jugado, la celda del minimapa del jugador y cambia las imagenes de la mazmorra a las que corresponde
	player.rotateRight();
	player_square->setRotation(player_square->getRotation() + 90.0f);
	
	dungeon.imagesToShow(images);
	s2->setTexture(images[2]);
	s1->setTexture(images[1]);
	s0->setTexture(images[0]);
}

void MapScene::rotateHalf(){
	//Modifica la direccion del jugado, la celda del minimapa del jugador y cambia las imagenes de la mazmorra a las que corresponde
	player.rotateRight();
	player.rotateRight();
	player_square->setRotation(player_square->getRotation() + 180.0f);
	
	dungeon.imagesToShow(images);
	s2->setTexture(images[2]);
	s1->setTexture(images[1]);
	s0->setTexture(images[0]);
}

void MapScene::move(){
	//Modifica la posicion del jugador, actualiza el minimapa y carga las imagenes correspondientes a la nueva posicion. Tambien comprueba si hay una batalla
	if(dungeon.canMove()){
		player.move();
		dungeon.imagesToShow(images);
		s2->setTexture(images[2]);
		s1->setTexture(images[1]);
		s0->setTexture(images[0]);
		minimap.cellsRevealedNerby(player.getX(), player.getY());
		for(int i = 0; i < minimap.SIZE*minimap.SIZE; i++){
			if(minimap.nerby[i]){
				minimap_images[i]->setTexture("square_revealed.png");
			}
			else{
				minimap_images[i]->setTexture("square.png");
			}
		}
		minimap.revealCell(player.getX(), player.getY());
	}
	//Aparicion enemigos, descomentar esto para hacer pruebas

	/*steps++;
	if((rand()%100) < 100*(1-(100/(100+steps*steps*steps)))){
		player_square->setTexture("square_exit.png");
		steps = 0;
	}
	else
		player_square->setTexture("square_player.png");*/
}


void MapScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event){
	//Hace la accion correspondiente a la tecla pulsada
	if(keyCode == EventKeyboard::KeyCode::KEY_W)
		move();
	if(keyCode == EventKeyboard::KeyCode::KEY_A)
		rotateLeft();
	if(keyCode == EventKeyboard::KeyCode::KEY_D)
		rotateRight();
	if(keyCode == EventKeyboard::KeyCode::KEY_S)
		rotateHalf();
	if(keyCode == EventKeyboard::KeyCode::KEY_Q)
		goToBattleScene(this);
}

void MapScene::goToBattleScene(Ref *pSender){
	//auto scene = BattleScene::createScene();

	BattleScene battle;
	battle.images[0] = this->images[0];
	battle.images[1] = this->images[1];
	battle.images[2] = this->images[2];
	battle.player = &player;
	auto scene = battle.createScene();

	/*for (int i = 0; i < 3; i++)
	{
		[i] = images[i];
	}*/

	Director::getInstance()->pushScene(scene);
}


