#ifndef __SceneTrans__ConfigScene__
#define __SceneTrans__ConfigScene__

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
#include "Obje.h"

class ConfigScene :
	public cocos2d::LayerColor//, public cocos2d::extension::EditBoxDelegate
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();


	CREATE_FUNC(ConfigScene);

	cocos2d::ui::Button* greenBtn;
	cocos2d::ui::Button* purpleBtn;

	cocos2d::Menu *SelectMenu;
	cocos2d::Menu *intervalMenu;
	cocos2d::Menu *setMenu;
	cocos2d::Menu *countMenu;


	virtual void update(float _fDelta);
	//void colorGreenSelect(Ref* psender);
	//void colorPurpleSelect(Ref* psender);

	void doMain(Ref* pSender);
	void intervalUp(Ref* pSender);
	void intervalDown(Ref* pSender);
	void setUp(Ref* pSender);
	void setDown(Ref* pSender);
	void countUp(Ref* pSender);
	void countDown(Ref* pSernder);

	cocos2d::Menu *basicMenu;
	cocos2d::Sprite *IntensitySprite;
	cocos2d::Sprite *settingSprite;
	cocos2d::Sprite *ColorEdge;
	cocos2d::Sprite *configCount;
	cocos2d::Sprite *configSet;
	cocos2d::Sprite *configInterval;
	cocos2d::Sprite *configColor;

	cocos2d::Label *configCountLabel;
	cocos2d::Label *configSetLabel;
	cocos2d::Label *configIntervalLabel;

	cocos2d::MenuItemImage *intervalUpBtn;
	cocos2d::MenuItemImage *intervalDownBtn;
	cocos2d::MenuItemImage *setUpBtn;
	cocos2d::MenuItemImage *setDownBtn;
	cocos2d::MenuItemImage *countUpBtn;
	cocos2d::MenuItemImage *countDownBtn;
};

#endif /* defined(__SceneTrans__ConfigScene__) */