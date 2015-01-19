#ifndef __WIN_SCENE_H__
#define __WIN_SCENE_H__

#include "cocos2d.h"

class WinScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    CREATE_FUNC(WinScene);

	void goToMainMenu(Ref *pSender);

private:

	/*-----MENU ELEMENTS-----*/
	cocos2d::LabelTTF *_gameOverText;
};

#endif
