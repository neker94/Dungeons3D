#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    CREATE_FUNC(GameOverScene);

	void goToMainMenu(Ref *pSender);
	void restart(Ref *pSender);

private:

	/*-----MENU ELEMENTS-----*/
	bool winner;
	cocos2d::LabelTTF *_gameOverText;

	cocos2d::MenuItemLabel *_restartButton;
	cocos2d::LabelTTF *_restartLabel;

	cocos2d::MenuItemLabel *_returnButton;
	cocos2d::LabelTTF *_returnLabel;
};

#endif // __MAP_SCENE_H__
