#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    CREATE_FUNC(MainMenuScene);

	void goToDungeonScene(Ref *pSender);

private:

	/*-----MENU ELEMENTS-----*/
	cocos2d::Sprite *background_menu_sprite;

	cocos2d::MenuItemImage *start_button;
};

#endif // __MAP_SCENE_H__
