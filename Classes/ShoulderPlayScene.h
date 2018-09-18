#ifndef __SceneTrans__ShoulderPlayScene__
#define __SceneTrans__ShoulderPlayScene__

#include "cocos2d.h" 
USING_NS_CC;

namespace Shoulder {
	class ShoulderPlayScene : public cocos2d::LayerColor
	{
	public:
		static cocos2d::Scene* createScene();

		virtual bool init();
		virtual void update(float _fDelta);
		CREATE_FUNC(ShoulderPlayScene);


		bool interval_flag;
		time_t start_interval;
		time_t end_interval;

		void static videoInput();
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
		cocos2d::Sprite *UpdownSprite;


	};

#endif /* defined(__SceneTrans__ShoulderPlayScene__) */

}