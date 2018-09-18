#include "ModeSelectScene.h"
#include "HelloWorldScene.h"
#include "SoloPlayScene.h"
#include "ShoulderPlayScene.h"
#include "SimpleAudioEngine.h"


using namespace::extension;
using namespace std;
USING_NS_CC;


Scene* ModeSelectScene::createScene()
{
	auto scene = Scene::create();

	auto layer = ModeSelectScene::create();

	scene->addChild(layer);

	return scene;
}

bool ModeSelectScene::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	this->setTouchEnabled(true);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size editBoxSize = Size(230, 90);

	SelectMode = Sprite::create("Images/SelectMode.png");
	SelectMode->setAnchorPoint(Vec2(0.5, 0.5));
	SelectMode->setScale(0.9f);
	SelectMode->setPosition(Vec2(visibleSize.width*0.47, visibleSize.height*0.9));
	SelectMode->setLocalZOrder(1);
	this->addChild(SelectMode);


	auto BackgroundSprite = Sprite::create("Images/Background.png");
	BackgroundSprite->setAnchorPoint(Vec2(0, 0));
	BackgroundSprite->setPosition(Vec2(0, 0));
	BackgroundSprite->setLocalZOrder(0);
	BackgroundSprite->setScale(1.55f);
	this->addChild(BackgroundSprite);


	auto exitem1 = MenuItemImage::create(
		"Images/Shoulder.png", "Images/Shoulder1.png",
		CC_CALLBACK_1(ModeSelectScene::doShoulder, this));
	auto exitem2 = MenuItemImage::create(
		"Images/Arm.png", "Images/Arm1.png",
		CC_CALLBACK_1(ModeSelectScene::doSolo, this));
	
	SelectMenu = Menu::create(exitem1, exitem2, nullptr);
	SelectMenu->alignItemsHorizontally();
	SelectMenu->alignItemsHorizontallyWithPadding(200);
	SelectMenu->setScale(1.1f);
	SelectMenu->setPosition(Vec2(origin.x + (visibleSize.width*0.55), origin.y + (visibleSize.height*0.8)));
	this->addChild(SelectMenu);

	auto backItem = MenuItemImage::create(
		"Images/BackTo.png", "Images/BackTo1.png",
		CC_CALLBACK_1(ModeSelectScene::doBack, this));

	BackMenu = Menu::create(backItem, nullptr);
	BackMenu->alignItemsHorizontally();
	BackMenu->alignItemsHorizontallyWithPadding(150);
	BackMenu->setScale(0.9f);
	BackMenu->setPosition(Vec2(origin.x + (visibleSize.width*0.85), origin.y + (visibleSize.height*0.03)));
	this->addChild(BackMenu);


	auto eduman = Sprite::create("Images/BodyModel1.png");
	eduman->setAnchorPoint(Vec2(0.5, 0.5));
	eduman->setPosition(Vec2(visibleSize.width*0.71, visibleSize.height*0.36));
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



	auto shoulderman = Sprite::create("Images/Bodymeling1.png");
	shoulderman->setAnchorPoint(Vec2(0.5, 0.5));
	shoulderman->setPosition(Vec2(visibleSize.width*0.32, visibleSize.height*0.36));
	this->addChild(shoulderman);

	auto shoulderAnimation = Animation::create();
	shoulderAnimation->setDelayPerUnit(0.05f);

	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling1.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling2.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling3.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling4.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling5.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling6.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling7.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling8.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling9.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling10.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling11.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling12.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling13.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling14.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling15.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling16.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling17.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling18.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling19.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling20.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling21.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling22.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling23.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling24.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling25.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling26.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling27.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling26.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling25.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling24.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling23.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling22.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling21.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling20.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling19.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling18.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling17.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling16.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling15.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling14.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling13.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling12.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling11.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling10.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling9.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling8.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling7.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling6.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling5.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling4.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling3.png");
	shoulderAnimation->addSpriteFrameWithFile("Images/Bodymeling2.png");

	auto shoulderAnimate = Animate::create(shoulderAnimation);
	auto shoulderRepeat = RepeatForever::create(shoulderAnimate);

	shoulderman->runAction(shoulderRepeat);

	return true;
}


void ModeSelectScene::doBack(Ref* pSender) {

	auto backScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(backScene);

}


void ModeSelectScene::doSolo(Ref* pSender) {
		
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		auto pScene = SoloPlayScene::createScene();
		Director::getInstance()->replaceScene(pScene);
}


void ModeSelectScene::doShoulder(Ref* pSender) {

	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	auto shoulderScene = Shoulder::ShoulderPlayScene::createScene();
	Director::getInstance()->replaceScene(shoulderScene);

}