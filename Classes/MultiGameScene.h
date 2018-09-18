#ifndef __SceneTrans__MultiGameScene__
#define __SceneTrans__MultiGameScene__

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
USING_NS_CC;

namespace Multi {
	class MultiGameScene : public cocos2d::LayerColor
	{
	public:
		static cocos2d::Scene* createScene();

		virtual bool init();
		virtual void update(float _fDelta);
		CREATE_FUNC(MultiGameScene);

		void MultiGameScene::showTurnSprite();

		bool interval_flag;
		time_t start_interval;
		time_t end_interval;

		void doClose(Ref* pSender);
		void doRecall(Ref* pSender);


		cocos2d::Menu *pMenu;


		cocos2d::Label *pLabel1;
		cocos2d::Label *SetLabel;
		cocos2d::Label *CountLabel;

		cocos2d::Sprite *EndSprite;
		cocos2d::Sprite *ModelSprite;
		cocos2d::Sprite *SetScore;
		cocos2d::Sprite *CountScore;
		cocos2d::Sprite *GuideSprite;
		cocos2d::Sprite *ReadySprite;
		cocos2d::Sprite *FightingSprite;
		cocos2d::Sprite *RestTimeSprite;
		cocos2d::Sprite *TurnSprite;

		cocos2d::Sprite *UpdownSprite;

	};

#endif /* defined(__SceneTrans__MultiGameScene__) */
}