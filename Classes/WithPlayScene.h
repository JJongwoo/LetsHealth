#ifndef __SceneTrans__WithPlayScene__
#define __SceneTrans__WithPlayScene__

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
USING_NS_CC;

class WithPlayScene : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(WithPlayScene);

	cocos2d::ui::Button *readyBtn;
	cocos2d::ui::Button *readyBtn2;
	cocos2d::ui::Button *MainBtn;


	cocos2d::Sprite *ExplainSprite;

	virtual void update(float _fDelta);


};

#endif /* defined(__SceneTrans__WithPlayScene__) */