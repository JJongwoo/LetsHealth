#include <iostream>
#include <string>

#include "networkManager.h"
#include "Protocol.h"
#include "cocos2d.h"

#include <time.h>

#include <thread>

using namespace std;



networkManager* networkManager::mInstance = NULL;
clock_t start = time(NULL);

networkManager * networkManager::getInstance() //싱글턴 패턴
{
	if (!mInstance)
	{
		mInstance = new networkManager();
		mInstance->init();
	}

	return mInstance;
}

bool networkManager::init()
{


	//thread thread_name(run);
	//thread_name.detach();


	return true;
}


void networkManager::connectServer(const char *pName, const char *pEndpoint)
{
	strncpy_s(mUserName, MAX_NAME_LEN, pName, MAX_NAME_LEN - 1);
	cocos2d::log("connectServer in");

	auto endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(pEndpoint), PORT_NUMBER);
	mEndPoint = endpoint;
	mAsioChatClient = new asioChatClient(*mIoServ);
	//auto schedule = cocos2d::Director::getInstance()->getScheduler();
	//schedule->performFunctionInCocosThread(CC_CALLBACK_0(networkManager::run, this));
	mAsioChatClient->connect(mEndPoint);
	boost::asio::io_service::work work(*mIoServ);
	boost::thread thread(boost::bind(&networkManager::runIoServ, this));

	//auto schedule = cocos2d::Director::getInstance()->getScheduler();
	//schedule->performFunctionInCocosThread(CC_CALLBACK_0(networkManager::runIoServ, this));

	//스케줄 io_service.run()
	//auto _service_thread = std::move(std::thread([this]() {
	//	mIoServ->run();
	//}));
	cocos2d::log("connectServer out");
}

networkManager::networkManager() //networkManager 클래스 생성자
{
	gameReady = MSGList::fail;
	gameStart = MSGList::fail;
	mIoServ = new boost::asio::io_service;
	gameTurn = MSGList::fail;
	gameAllReady = MSGList::fail;
	gameResult = MSGList::fail;
	//boost::asio::io_service::work work(*mIoServ);

}


void networkManager::runIoServ()//스레드 돌리기
{
	cocos2d::log("into runIoServ");
	//mAsioChatClient = new asioChatClient(*mIoServ);
	//mAsioChatClient->connect(mEndPoint);

	//cocos2d::log("after connect");
	//boost::thread thre(boost::bind(&boost::asio::io_service::run, mIoServ));
	mIoServ->run();
	cocos2d::log("runIoServ good bye");

}




void networkManager::failConnect()
{
	cocos2d::log("failConnect");
}

void networkManager::succeedConnect()
{
	cocos2d::log("succeedConnect in");
	//로그인
	PKT_REQ_IN sendPkt;
	sendPkt.Init();

	strncpy_s(sendPkt.szName, MAX_NAME_LEN, mUserName, MAX_NAME_LEN - 1);
	//auto schedule = cocos2d::Director::getInstance()->getScheduler();
	//schedule->performFunctionInCocosThread(CC_CALLBACK_0(asioChatClient::postSend, mAsioChatClient,false, sendPkt.nSize, (char*)&sendPkt));
	mAsioChatClient->postSend(false, sendPkt.nSize, (char*)&sendPkt);

	//scene전환

	//화면 전환용 인데 일시 보류임
	//auto roomScene = chatRoomScene::createScene();
	//cocos2d::Director::getInstance()->replaceScene(roomScene);
	//포스트리시브
	cocos2d::log("succeedConnect out");
}
void networkManager::succeedFail() {
	cout << " 게임에서 졌습니다." << endl;
	this->gameResult = MSGList::gameLose;
	PKT_NOTICE_GAME sendPkt;
	sendPkt.Init();
	strncpy_s(sendPkt.szName, MAX_NAME_LEN, mUserName, MAX_NAME_LEN - 1);
	sendPkt.gameReady = this->gameReady;
	sendPkt.gameResult = this->gameResult;
	sendPkt.gameStart = this->gameStart;
	mAsioChatClient->postSend(false, sendPkt.nSize, (char*)&sendPkt);

}
void networkManager::succeedSend()
{
	cocos2d::log("succeedSend in");
	//로그인
	PKT_REQ_CHAT sendPkt;
	sendPkt.Init();
	strncpy_s(sendPkt.szMessage, MAX_NAME_LEN, "hi", MAX_NAME_LEN - 1);
	cocos2d::log("%s", sendPkt.szMessage);
	mAsioChatClient->postSend(false, sendPkt.nSize, (char*)&sendPkt);
	//scene전환

	//화면 전환용 인데 일시 보류임
	//auto roomScene = chatRoomScene::createScene();
	//cocos2d::Director::getInstance()->replaceScene(roomScene);
	//포스트리시브


}

void networkManager::succeedReady()
{
	if (gameReady == MSGList::fail) {
		gameReady == MSGList::gameReady;

		//래디
		PKT_NOTICE_GAME sendPkt;
		sendPkt.Init();
		strncpy_s(sendPkt.szName, MAX_NAME_LEN, mUserName, MAX_NAME_LEN - 1);
		sendPkt.gameReady = MSGList::gameReady;

		mAsioChatClient->postSend(false, sendPkt.nSize, (char*)&sendPkt);
	}
	else if (gameReady == MSGList::gameReady)
	{
		gameReady == MSGList::n_gameReady;
		cocos2d::log("succeedReady in");
		//래디
		PKT_NOTICE_GAME sendPkt;
		sendPkt.Init();
		strncpy_s(sendPkt.szName, MAX_NAME_LEN, mUserName, MAX_NAME_LEN - 1);
		sendPkt.gameReady = MSGList::n_gameReady;

		mAsioChatClient->postSend(false, sendPkt.nSize, (char*)&sendPkt);
		//scene전환
	}
	else if (gameReady == MSGList::n_gameReady) {

		gameReady == MSGList::gameReady;
		cocos2d::log("succeedReady in");
		//로그인
		PKT_NOTICE_GAME sendPkt;
		sendPkt.Init();
		strncpy_s(sendPkt.szName, MAX_NAME_LEN, mUserName, MAX_NAME_LEN - 1);
		sendPkt.gameReady = MSGList::gameReady;

		mAsioChatClient->postSend(false, sendPkt.nSize, (char*)&sendPkt);
	}
}

void networkManager::succeedTurn() {
	if (this->gameTurn == MSGList::fail) { //turn이 처음 접근 했음
		cout << "gameTyurnb faildlfEo  " << endl;
		PKT_NOTICE_TURN sendPkt;
		sendPkt.Init();
		strncpy_s(sendPkt.szName, MAX_NAME_LEN, mUserName, MAX_NAME_LEN - 1);
		sendPkt.allReady = MSGList::gameReady;//나 turn 임을 보낸다.
		mAsioChatClient->postSend(false, sendPkt.nSize, (char*)&sendPkt);

	}
	else {
		cocos2d::log("succeedTurn in");
		//게임 턴 바꾸기
		PKT_NOTICE_TURN sendPkt;
		sendPkt.Init();
		strncpy_s(sendPkt.szName, MAX_NAME_LEN, mUserName, MAX_NAME_LEN - 1);
		sendPkt.gameTurn = MSGList::turn; //나 turn 임을 보낸다.


										  //그리고 자체적으로 turn을 바꾼다
		networkManager::getInstance()->gameTurn = MSGList::n_turn;


		mAsioChatClient->postSend(false, sendPkt.nSize, (char*)&sendPkt);


	}

}

void networkManager::succeedAllReady() {

	//그 y값이 -1이 아니면 게임 turn을 받기 위해서 보내는 거임
	PKT_NOTICE_TURN sendPkt;
	sendPkt.Init();
	strncpy_s(sendPkt.szName, MAX_NAME_LEN, mUserName, MAX_NAME_LEN - 1);
	sendPkt.gameTurn = MSGList::turn; //나 turn 임을 보낸다.


									  //그리고 자체적으로 turn을 바꾼다
	networkManager::getInstance()->gameTurn = MSGList::n_turn;


	mAsioChatClient->postSend(false, sendPkt.nSize, (char*)&sendPkt);
	//scene전환

}






void networkManager::disConnect()
{
	mAsioChatClient->closeConnect();
}







