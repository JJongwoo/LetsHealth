#ifndef __SceneTrans__ModeSelectScene__
#define __SceneTrans__ModeSelectScene__

#include "cocos2d.h"
#include "extensions\cocos-ext.h"

class ModeSelectScene : 
	public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(ModeSelectScene);

	cocos2d::Menu *SelectMenu;
	cocos2d::Menu *BackMenu;

	void doBack(Ref* pSender);
	void doSolo(Ref* pSender);
	void doShoulder(Ref* pSender);


	cocos2d::Sprite *SelectMode;

	 
	
};

#endif /* defined(__SceneTrans__ModeSelectScene__) */

