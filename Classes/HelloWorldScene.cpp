#include "HelloWorldScene.h"

#include "HelloWorldScene.h"
#include "audio/include/SimpleAudioEngine.h"
#include "SoloPlayScene.h"
#include "ConfigScene.h"
#include "ModeSelectScene.h"
#include "WithPlayScene.h"

#include "networkManager.h"

#include <time.h>


using namespace CocosDenshion;
USING_NS_CC;

//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

static clock_t start = time(NULL);


Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}


bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first

	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//메뉴

	auto item1 = MenuItemImage::create(
		"Images/SoloPlayButton.png", "Images/SoloPlayButton1.png",
		CC_CALLBACK_1(HelloWorld::doModeSelectScene, this));

	auto item2 = MenuItemImage::create(
		"Images/TogetherPlayButton.png", "Images/TogetherPlayButton1.png",
		CC_CALLBACK_1(HelloWorld::doWithScene, this));

	auto item3 = MenuItemImage::create(
		"Images/SettingButton.png", "Images/SettingButton1.png",
		CC_CALLBACK_1(HelloWorld::doConfigScene, this));

	auto item4 = MenuItemImage::create(
		"Images/QuitButton.png", "Images/QuitButton1.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	// 메뉴 생성
	auto pMenu = Menu::create(item1, item2, item3, item4, nullptr);

	// 메뉴 정렬
	pMenu->alignItemsVertically();
	pMenu->setScale(0.9f);
	pMenu->setPosition(Vec2(origin.x + (visibleSize.width*0.45), origin.y + (visibleSize.height*0.15)));
	pMenu->setLocalZOrder(2);

	// 레이어에 메뉴 객체 추가
	this->addChild(pMenu);

	auto wlayer = LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(wlayer);


	TitleNameSprite = Sprite::create("Images/Title.png");
	TitleNameSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*0.75));
	TitleNameSprite->setLocalZOrder(2);
	TitleNameSprite->setScale(1.8f);
	this->addChild(TitleNameSprite, 2);
	this->ActionSpawn(this);

	
	bool a = SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();
	if (!a) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/MainBgm.mp3", true);
	}

	auto pRunner = Sprite::create("Images/TitleRunner1.png");
	pRunner->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.3));
	pRunner->setScale(1.5f);
	pRunner->setLocalZOrder(2);
	this->addChild(pRunner);


	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	animation->addSpriteFrameWithFile("Images/TitleRunner1.png");
	animation->addSpriteFrameWithFile("Images/TitleRunner2.png");
	animation->addSpriteFrameWithFile("Images/TitleRunner3.png");
	animation->addSpriteFrameWithFile("Images/TitleRunner4.png");
	animation->addSpriteFrameWithFile("Images/TitleRunner5.png");
	animation->addSpriteFrameWithFile("Images/TitleRunner6.png");
	auto animate = Animate::create(animation);

	auto rep = RepeatForever::create(animate);
	pRunner->runAction(rep);   // 반복 실행

	auto background = Sprite::create("Images/TitleBackground.png");
	background->setAnchorPoint(Vec2(0, 0));

	auto voidNode = ParallaxNode::create();
	voidNode->addChild(background, 0, Vec2(1.0f, 1.0f), Vec2(0, 0));

	auto backgroundani = Animation::create();
	auto go = MoveBy::create(2, Vec2(-500, 0));
	auto goBack = MoveTo::create(0, Vec2(0, 0));
	auto seq = Sequence::create(go, goBack, NULL);
	auto act = RepeatForever::create(seq);
	voidNode->runAction(act);
	this->addChild(voidNode);

	return true;
}

void HelloWorld::ActionSpawn(Ref* pSender)
{

	auto action = Sequence::create(
		RotateBy::create(0.5, 8),
		RotateBy::create(0.5, -8),
		RotateBy::create(0.5, -8),
		RotateBy::create(0.5, 8),
		nullptr);
	auto rep = RepeatForever::create(action);

	TitleNameSprite->runAction(rep);
}
void HelloWorld::doModeSelectScene(Ref* pSender) {


	auto pScene = ModeSelectScene::createScene();
	Director::getInstance()->replaceScene(pScene);
}
void HelloWorld::doSoloScene(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	auto pScene = SoloPlayScene::createScene();
	Director::getInstance()->replaceScene(pScene);

}

void HelloWorld::doWithScene(Ref* pSender)
{
	//thread thread_name(networkrun);
	//thread_name.detach();

	boost::asio::io_service io_service;
	boost::asio::ip::tcp::resolver resolver(io_service);
	boost::asio::ip::tcp::resolver::query query(boost::asio::ip::host_name(), "");
	boost::asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
	boost::asio::ip::tcp::resolver::iterator end; // End marker.

	string nickName;
	for (int i = 0; i<2; i++)
	{

		boost::asio::ip::tcp::endpoint ep = *iter++;
		std::cout << ep << std::endl;
		if (i == 1)
			nickName = ep.address().to_string();
	}
	cout << "안녕하세요"<< nickName << endl;
	log(nickName.c_str());

	log("what the fuck");
	networkManager::getInstance()->connectServer(nickName.c_str(), "192.168.0.8");
	//"127.0.0.1"
	log("good bye good bye");
	//auto endpoint = boost::asio::ip::tcp::endpoint(
	//	boost::asio::ip::address::from_string("127.0.0.1"),
	//PORT_NUMBER);
	//서버연결


	//auto schedule = cocos2d::Director::getInstance()->getScheduler();
	//schedule->performFunctionInCocosThread(CC_CALLBACK_0(HelloWorld::runrun, this));
	log("what the fuck2");
	//ChatClient Cliet(io_service);
	//Cliet.Connect(endpoint); //연결 시도

	//boost::thread thread(boost::bind(&boost::asio::io_service::run, &io_service)); //bind 해서 스레드?


	//	char szInputMessage[MAX_MESSAGE_LEN * 2] = { 0, };
	log("oh my god");


	auto withScene = WithPlayScene::createScene();

	Director::getInstance()->replaceScene(withScene); // 씬 넘어감
}
void HelloWorld::doConfigScene(Ref* pSender)
{
	auto pScene = ConfigScene::createScene();
	Director::getInstance()->pushScene(pScene);
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}


