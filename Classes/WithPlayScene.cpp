#include "WithPlayScene.h"
#include "HelloWorldScene.h"
#include "MultiGameScene.h"
#include "Obje.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<time.h>
#include <thread>
#include <sstream>
#include <string>
#include "opencv\cv.h"
#include "opencv\highgui.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>

#include "Protocol.h"
#include "networkManager.h"

#include <time.h>


using namespace cocos2d::extension;
using namespace std;
using namespace cv;
USING_NS_CC;


bool ready_flag = false;

void jhp(Ref* pSender);
void doMain(Ref* pSender);

Scene* WithPlayScene::createScene()
{
	auto scene = Scene::create();

	auto layer = WithPlayScene::create();

	scene->addChild(layer);

	return scene;
}

bool WithPlayScene::init()
{
	cout << "park jung hwan" << endl;
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	ready_flag = false;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto BackgroundSprite = Sprite::create("Images/Background.png");
	BackgroundSprite->setAnchorPoint(Vec2(0, 0));
	BackgroundSprite->setPosition(Vec2(0, 0));
	BackgroundSprite->setLocalZOrder(0);
	BackgroundSprite->setScale(1.55f);
	this->addChild(BackgroundSprite);


	readyBtn = ui::Button::create("Images/ReadyBtn.png", "Images/ReadyBtn2.png");
	readyBtn->setLocalZOrder(1);
	readyBtn->setAnchorPoint(Vec2(0, 0));
	readyBtn->setPosition(Vec2(visibleSize.width*0.52, visibleSize.height*0.13));
	readyBtn->addClickEventListener(CC_CALLBACK_0(jhp, this));
	this->addChild(readyBtn);

	readyBtn2 = ui::Button::create("Images/ReadyBtn2.png", "Images/ReadyBtn.png");
	readyBtn2->setLocalZOrder(2);
	readyBtn2->setAnchorPoint(Vec2(0, 0));
	readyBtn2->setPosition(Vec2(visibleSize.width*0.52, visibleSize.height*0.13));
	readyBtn2->addClickEventListener(CC_CALLBACK_0(jhp, this));
	readyBtn2->setVisible(false);
	this->addChild(readyBtn2);
	
	MainBtn = ui::Button::create("Images/ToMain.png", "Images/ToMain1.png");
	MainBtn->setAnchorPoint(Vec2(0, 0));
	MainBtn->setPosition(Vec2(visibleSize.width*0.51, visibleSize.height*0.01));
	MainBtn->addClickEventListener(CC_CALLBACK_0(doMain, this));
	this->addChild(MainBtn); 

	ExplainSprite = Sprite::create("Images/Explanation.png");
	ExplainSprite->setAnchorPoint(Vec2(0, 0));
	ExplainSprite->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.3));

	auto ExplainFadeOut = FadeOut::create(0);
	auto ExplainFadeIn = FadeIn::create(2.5);
	auto ExplainSeq = Sequence::create(ExplainFadeOut, ExplainFadeIn, nullptr);

	ExplainSprite->runAction(ExplainSeq);

	this->addChild(ExplainSprite);

	auto eduman = Sprite::create("Images/BodyModel1.png");
	eduman->setAnchorPoint(Vec2(0.5, 0.5));
	eduman->setPosition(Vec2(visibleSize.width*0.25, visibleSize.height*0.5));
	this->addChild(eduman);

	auto eduAnimation = Animation::create();
	eduAnimation->setDelayPerUnit(0.05f);

	eduAnimation->addSpriteFrameWithFile("Images/BodyModel1.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel2.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel3.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel4.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel5.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel6.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel7.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel8.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel9.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel10.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel11.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel12.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel13.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel14.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel15.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel16.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel17.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel18.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel19.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel20.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel21.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel22.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel23.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel22.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel21.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel20.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel19.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel18.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel17.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel16.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel15.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel14.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel13.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel12.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel11.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel10.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel9.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel8.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel7.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel6.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel5.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel4.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel3.png");
	eduAnimation->addSpriteFrameWithFile("Images/BodyModel2.png");

	auto eduAnimate = Animate::create(eduAnimation);
	auto eduRepeat = RepeatForever::create(eduAnimate);

	eduman->runAction(eduRepeat);

	this->scheduleUpdate();
	return true;
}

void WithPlayScene::update(float dt)
{
	/*if (MSGList::gameStart == networkManager::getInstance()->startGame) {
		log("okok good");
		auto pScene = Multi::MultiGameScene::createScene();
		Director::getInstance()->replaceScene(pScene);
	}
	*/
	if (ready_flag == true) {
		readyBtn->setVisible(false);
		readyBtn2->setVisible(true);
	}
	else if (ready_flag == false) {
		readyBtn->setVisible(true);
		readyBtn2->setVisible(false);
	}

	if (MSGList::gameStart == networkManager::getInstance()->gameStart) {
		log("okok good");
		auto pScene = Multi::MultiGameScene::createScene();
		Director::getInstance()->replaceScene(pScene);
	}
}

void doMain(Ref* pSender)
{
	auto pScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(pScene);
}


void jhp(Ref* pSender)
{
	cout << "안녕허세요" << MSGList::fail << endl;

	log("this is button");
	//서버연결
	if (ready_flag == false) {
		networkManager::getInstance()->succeedReady();
		ready_flag = true;
	}



}
