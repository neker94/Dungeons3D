#include "cocos2d.h"

class BattleScene : public cocos2d::Layer
{
public:
	BattleScene();

	static cocos2d::Scene* createScene();
	virtual bool init();
	void returnToMapScene(Ref *pSender);

	const char *images [3];

};

