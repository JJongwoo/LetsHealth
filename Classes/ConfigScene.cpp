#include "ConfigScene.h"
#include "HelloWorldScene.h"
#include "KoreanUTF8.h"

using namespace cocos2d::extension;
using namespace std;
using namespace cv;
USING_NS_CC;

void colorPurpleSelect(Ref* pSender);
void colorGreenSelect(Ref* pSender);

bool color_flag = true;

string ExerciseCount[5] = {"3","5","10","12","15" };
string ExerciseSet[5] = {"3","4","5","6","7"};
string ExerciseInterval[3] = {"7","10","60"};

int setIndex = 0;
int countIndex = 0;
int intervalIndex = 0;

Scene* ConfigScene::createScene()
{
	auto scene = Scene::create();

	auto layer = ConfigScene::create();
	 
	scene->addChild(layer);

	return scene;
}

bool ConfigScene::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	auto BackgroundSprite = Sprite::create("Images/Background.png");
	BackgroundSprite->setAnchorPoint(Vec2(0, 0));
	BackgroundSprite->setPosition(Vec2(0, 0));
	BackgroundSprite->setLocalZOrder(0); 
	BackgroundSprite->setScale(1.55f);
	this->addChild(BackgroundSprite);

	this->setTouchEnabled(true);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	UserDefault::getInstance()->setStringForKey("ExerciseCount", "3");
	UserDefault::getInstance()->setStringForKey("ExerciseSet", "3");
	UserDefault::getInstance()->setStringForKey("ExerciseInterval", ExerciseInterval[intervalIndex]);
	
	
	auto settingSprite = cocos2d::Sprite::create("Images/Setting.png");
	settingSprite->setAnchorPoint(Vec2(0, 0));
	settingSprite->setPosition(Vec2(0, visibleSize.height*0.85));
	settingSprite->setScale(1.0f);
	settingSprite->setLocalZOrder(2);
	this->addChild(settingSprite);

	IntensitySprite = cocos2d::Sprite::create("Images/ConfigIntensity.png");
	IntensitySprite->setAnchorPoint(Vec2(0, 0));
	IntensitySprite->setPosition(Vec2(visibleSize.width*0.03, visibleSize.height*0.73));
	IntensitySprite->setScale(0.8f);
	IntensitySprite->setLocalZOrder(2);
	this->addChild(IntensitySprite);
	
	configCount = cocos2d::Sprite::create("Images/CountScore.png");
	configCount->setAnchorPoint(Vec2(0, 0));
	configCount->setScale(0.65f);
	configCount->setPosition(Vec2(visibleSize.width*0.13, visibleSize.height*0.65));
	configCount->setLocalZOrder(2);
	this->addChild(configCount);

	configSet = cocos2d::Sprite::create("Images/SetScore.png");
	configSet->setAnchorPoint(Vec2(0, 0));
	configSet->setPosition(Vec2(visibleSize.width*0.55, visibleSize.height*0.65));
	configSet->setLocalZOrder(2);
	configSet->setScale(0.65f);
	this->addChild(configSet);

	configInterval = cocos2d::Sprite::create("Images/ConfigInterval.png");
	configInterval->setAnchorPoint(Vec2(0, 0));
	configInterval->setPosition(Vec2(visibleSize.width*0.13, visibleSize.height*0.55));
	configInterval->setScale(0.65f);
	configInterval->setLocalZOrder(2);
	this->addChild(configInterval);
	
	TTFConfig ttfConfig("fonts/NanumGothicCoding.ttf", 42, GlyphCollection::DYNAMIC, nullptr, true);
	configIntervalLabel = cocos2d::Label::createWithTTF(ttfConfig, ExerciseInterval[intervalIndex], TextHAlignment::LEFT);
	configIntervalLabel->setString(UTF8(ExerciseInterval[intervalIndex] + " 초"));
	configIntervalLabel->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.56));
	configIntervalLabel->setColor(Color3B::WHITE);
	configIntervalLabel->setAnchorPoint(Vec2(0, 0));
	configIntervalLabel->enableOutline(Color4B::BLACK, 2);
	configIntervalLabel->enableShadow(Color4B::BLACK, cocos2d::Size(2, -2));
	configIntervalLabel->setLocalZOrder(2);
	this->addChild(configIntervalLabel);

	intervalUpBtn = MenuItemImage::create("Images/ConfigUpButton.png", "Images/ConfigUpButton1.png", CC_CALLBACK_1(ConfigScene::intervalUp, this));
	intervalDownBtn = MenuItemImage::create("Images/ConfigDownButton.png", "Images/ConfigDownButton1.png", CC_CALLBACK_1(ConfigScene::intervalDown, this));
	intervalMenu = Menu::create(intervalUpBtn, intervalDownBtn, nullptr);
	intervalMenu->alignItemsVertically();
	intervalMenu->setPosition(Vec2(visibleSize.width*0.54, visibleSize.height*0.58));
	intervalMenu->setLocalZOrder(2);
	this->addChild(intervalMenu);

	auto configColor = cocos2d::Sprite::create("Images/ConfigColor.png");
	configColor->setAnchorPoint(Vec2(0, 0));
	configColor->setPosition(Vec2(visibleSize.width*0.03, visibleSize.height*0.32));
	configColor->setScale(0.8f);
	configColor->setLocalZOrder(2);
	this->addChild(configColor);
	
	countUpBtn = MenuItemImage::create("Images/ConfigUpButton2.png", "Images/ConfigUpButton3.png", CC_CALLBACK_1(ConfigScene::countUp, this));
	countDownBtn = MenuItemImage::create("Images/ConfigDownButton2.png", "Images/ConfigDownButton3.png", CC_CALLBACK_1(ConfigScene::countDown, this));
	countMenu = Menu::create(countUpBtn, countDownBtn, nullptr);
	countMenu->alignItemsVertically();
	countMenu->setPosition(Vec2(visibleSize.width*0.53, visibleSize.height*0.68));
	countMenu->setLocalZOrder(2);
	this->addChild(countMenu);

	configCountLabel = cocos2d::Label::createWithTTF(ttfConfig, ExerciseCount[countIndex], TextHAlignment::CENTER);
	configCountLabel->setString(UTF8(ExerciseCount[countIndex]+" 회"));
	configCountLabel->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.66 ));
	configCountLabel->setColor(Color3B::WHITE);
	configCountLabel->setAnchorPoint(Vec2(0, 0));
	configCountLabel->enableOutline(Color4B::BLACK, 2);
	configCountLabel->enableShadow(Color4B::BLACK, cocos2d::Size(2, -2));
	configCountLabel->setLocalZOrder(2);
	this->addChild(configCountLabel);

	setUpBtn = MenuItemImage::create("Images/ConfigUpButton.png", "Images/ConfigUpButton1.png", CC_CALLBACK_1(ConfigScene::setUp, this));
	setDownBtn = MenuItemImage::create("Images/ConfigDownButton.png", "Images/ConfigDownButton1.png", CC_CALLBACK_1(ConfigScene::setDown, this));
	setMenu = Menu::create(setUpBtn, setDownBtn, nullptr);
	setMenu->alignItemsVertically();
	setMenu->setPosition(Vec2(visibleSize.width*0.95, visibleSize.height*0.68));
	setMenu->setLocalZOrder(2);
	this->addChild(setMenu);

	configSetLabel = cocos2d::Label::createWithTTF(ttfConfig, ExerciseSet[setIndex], TextHAlignment::CENTER);
	configSetLabel->setString(UTF8(ExerciseSet[setIndex] + " 세트"));
	configSetLabel->setPosition(Vec2(visibleSize.width*0.78, visibleSize.height*0.66));
	configSetLabel->setColor(Color3B::WHITE);
	configSetLabel->setAnchorPoint(Vec2(0, 0));
	configSetLabel->enableOutline(Color4B::BLACK, 2);
	configSetLabel->enableShadow(Color4B::BLACK, cocos2d::Size(2, -2));
	configSetLabel->setLocalZOrder(2);
	this->addChild(configSetLabel);
	 
	
	auto configMenu = MenuItemImage::create("Images/ConfigToMain.png", "Images/ConfigToMain1.png",
		CC_CALLBACK_1(ConfigScene::doMain, this));
	
	auto basicMenu = Menu::create(configMenu, nullptr);
	basicMenu->alignItemsHorizontally();
	basicMenu->alignItemsHorizontallyWithPadding(100);
	basicMenu->setAnchorPoint(Vec2(0, 0));
	basicMenu->setScale(1.0f);
	basicMenu->setPosition(Vec2(origin.x + (visibleSize.width*0.75), origin.y + (visibleSize.height*0.07)));

	this->addChild(basicMenu);


	greenBtn = ui::Button::create("Images/GreenColor.png");
	purpleBtn = ui::Button::create("Images/PurpleColor.png");
	 
	greenBtn->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.25));
	purpleBtn->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.25));

	greenBtn->setLocalZOrder(2);
	purpleBtn->setLocalZOrder(2);

	greenBtn->addClickEventListener(CC_CALLBACK_0(colorGreenSelect, this));
	purpleBtn->addClickEventListener(CC_CALLBACK_0(colorPurpleSelect, this));

	this->addChild(greenBtn);
	this->addChild(purpleBtn);

	ColorEdge = cocos2d::Sprite::create("Images/SelectedColor.png");
	ColorEdge->setLocalZOrder(2);
	ColorEdge->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.25));

	this->addChild(ColorEdge);
	this->scheduleUpdate();

	return true;
}

void ConfigScene::update(float dt) {
	auto visibleSize = Director::getInstance()->getVisibleSize();

	if (color_flag == true) {
		ColorEdge->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.25));
	}
	else {
		ColorEdge->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.25));
	}

	configSetLabel->setString(UTF8(ExerciseSet[setIndex] + " 세트"));
	configCountLabel->setString(UTF8(ExerciseCount[countIndex] + " 회"));
	configIntervalLabel->setString(UTF8(ExerciseInterval[intervalIndex] + " 초"));
}

void ConfigScene::doMain(Ref* pSender) {
	auto pScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(pScene);
	//Director::getInstance()->popScene();
}


void colorPurpleSelect(Ref* psender)
{
	color_flag = false;
	UserDefault::getInstance()->setStringForKey("ColorInfo", "purple");
	log("haha");
}

void colorGreenSelect(Ref* psender)
{
	color_flag = true;
	UserDefault::getInstance()->setStringForKey("ColorInfo", "green");
	log("hahaha");
}

void ConfigScene::intervalUp(Ref* pSender) {
	if (intervalIndex < 2) {
		intervalIndex++;
	}
	else {
		intervalIndex = 0;
	}
	UserDefault::getInstance()->setStringForKey("ExerciseInterval", ExerciseInterval[intervalIndex]);
}

void ConfigScene::intervalDown(Ref* pSender) {
	if (intervalIndex > 0) {
		intervalIndex--;
	}
	else {
		intervalIndex = 2;
	}
	UserDefault::getInstance()->setStringForKey("ExerciseInterval", ExerciseInterval[intervalIndex]);
}
void ConfigScene::setUp(Ref* pSender)
{
	if (setIndex < 4) {
		setIndex++;
	}
	else {
		setIndex = 0;
	}
	UserDefault::getInstance()->setStringForKey("ExerciseSet", ExerciseSet[setIndex]);
}
void ConfigScene::setDown(Ref* pSender)
{
	if (setIndex > 0) {
		setIndex--;
	}
	else {
		setIndex = 4;
	}
	UserDefault::getInstance()->setStringForKey("ExerciseSet", ExerciseSet[setIndex]);
}
void ConfigScene::countUp(Ref* pSender)
{
	string ret;
	if (countIndex < 4) {
		countIndex++;
	}
	else {
		countIndex = 0;
	}
	UserDefault::getInstance()->setStringForKey("ExerciseCount", ExerciseCount[countIndex]);
	ret = UserDefault::getInstance()->getStringForKey("ExerciseCount");
	log("%s", ret.c_str());
}
void ConfigScene::countDown(Ref* pSender)
{
	if (countIndex > 0) {
		countIndex--;
	}
	else {
		countIndex = 4;
	}
	UserDefault::getInstance()->setStringForKey("ExerciseCount", ExerciseCount[countIndex]);
}