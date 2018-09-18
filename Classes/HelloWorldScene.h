#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__


#include "cocos2d.h"



class HelloWorld : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

	cocos2d::Sprite* TitleSprite;
	cocos2d::Sprite* TitleNameSprite;
	cocos2d::Sprite* TitleEf1;
	cocos2d::Sprite* TitleEf2;

	void doSoloScene(Ref* pSender);
	void doModeSelectScene(Ref* pSender);
	void doWithScene(Ref* pSender);
	void doConfigScene(Ref* pSender);
	void doQuit(Ref* pSender);


	void doAction(Ref* pSender);
	void doReverse(Ref* pSender);
	void ActionSpawn(Ref* pSender);


};




#endif // __HELLOWORLD_SCENE_H__
