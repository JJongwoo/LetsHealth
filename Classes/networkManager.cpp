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

networkManager * networkManager::getInstance() //�̱��� ����
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

	//������ io_service.run()
	//auto _service_thread = std::move(std::thread([this]() {
	//	mIoServ->run();
	//}));
	cocos2d::log("connectServer out");
}

networkManager::networkManager() //networkManager Ŭ���� ������
{
	gameReady = MSGList::fail;
	gameStart = MSGList::fail;
	mIoServ = new boost::asio::io_service;
	gameTurn = MSGList::fail;
	gameAllReady = MSGList::fail;
	gameResult = MSGList::fail;
	//boost::asio::io_service::work work(*mIoServ);

}


void networkManager::runIoServ()//������ ������
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
	//�α���
	PKT_REQ_IN sendPkt;
	sendPkt.Init();

	strncpy_s(sendPkt.szName, MAX_NAME_LEN, mUserName, MAX_NAME_LEN - 1);
	//auto schedule = cocos2d::Director::getInstance()->getScheduler();
	//schedule->performFunctionInCocosThread(CC_CALLBACK_0(asioChatClient::postSend, mAsioChatClient,false, sendPkt.nSize, (char*)&sendPkt));
	mAsioChatClient->postSend(false, sendPkt.nSize, (char*)&sendPkt);

	//scene��ȯ

	//ȭ�� ��ȯ�� �ε� �Ͻ� ������
	//auto roomScene = chatRoomScene::createScene();
	//cocos2d::Director::getInstance()->replaceScene(roomScene);
	//����Ʈ���ú�
	cocos2d::log("succeedConnect out");
}
void networkManager::succeedFail() {
	cout << " ���ӿ��� �����ϴ�." << endl;
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
	//�α���
	PKT_REQ_CHAT sendPkt;
	sendPkt.Init();
	strncpy_s(sendPkt.szMessage, MAX_NAME_LEN, "hi", MAX_NAME_LEN - 1);
	cocos2d::log("%s", sendPkt.szMessage);
	mAsioChatClient->postSend(false, sendPkt.nSize, (char*)&sendPkt);
	//scene��ȯ

	//ȭ�� ��ȯ�� �ε� �Ͻ� ������
	//auto roomScene = chatRoomScene::createScene();
	//cocos2d::Director::getInstance()->replaceScene(roomScene);
	//����Ʈ���ú�


}

void networkManager::succeedReady()
{
	if (gameReady == MSGList::fail) {
		gameReady == MSGList::gameReady;

		//����
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
		//����
		PKT_NOTICE_GAME sendPkt;
		sendPkt.Init();
		strncpy_s(sendPkt.szName, MAX_NAME_LEN, mUserName, MAX_NAME_LEN - 1);
		sendPkt.gameReady = MSGList::n_gameReady;

		mAsioChatClient->postSend(false, sendPkt.nSize, (char*)&sendPkt);
		//scene��ȯ
	}
	else if (gameReady == MSGList::n_gameReady) {

		gameReady == MSGList::gameReady;
		cocos2d::log("succeedReady in");
		//�α���
		PKT_NOTICE_GAME sendPkt;
		sendPkt.Init();
		strncpy_s(sendPkt.szName, MAX_NAME_LEN, mUserName, MAX_NAME_LEN - 1);
		sendPkt.gameReady = MSGList::gameReady;

		mAsioChatClient->postSend(false, sendPkt.nSize, (char*)&sendPkt);
	}
}

void networkManager::succeedTurn() {
	if (this->gameTurn == MSGList::fail) { //turn�� ó�� ���� ����
		cout << "gameTyurnb faildlfEo  " << endl;
		PKT_NOTICE_TURN sendPkt;
		sendPkt.Init();
		strncpy_s(sendPkt.szName, MAX_NAME_LEN, mUserName, MAX_NAME_LEN - 1);
		sendPkt.allReady = MSGList::gameReady;//�� turn ���� ������.
		mAsioChatClient->postSend(false, sendPkt.nSize, (char*)&sendPkt);

	}
	else {
		cocos2d::log("succeedTurn in");
		//���� �� �ٲٱ�
		PKT_NOTICE_TURN sendPkt;
		sendPkt.Init();
		strncpy_s(sendPkt.szName, MAX_NAME_LEN, mUserName, MAX_NAME_LEN - 1);
		sendPkt.gameTurn = MSGList::turn; //�� turn ���� ������.


										  //�׸��� ��ü������ turn�� �ٲ۴�
		networkManager::getInstance()->gameTurn = MSGList::n_turn;


		mAsioChatClient->postSend(false, sendPkt.nSize, (char*)&sendPkt);


	}

}

void networkManager::succeedAllReady() {

	//�� y���� -1�� �ƴϸ� ���� turn�� �ޱ� ���ؼ� ������ ����
	PKT_NOTICE_TURN sendPkt;
	sendPkt.Init();
	strncpy_s(sendPkt.szName, MAX_NAME_LEN, mUserName, MAX_NAME_LEN - 1);
	sendPkt.gameTurn = MSGList::turn; //�� turn ���� ������.


									  //�׸��� ��ü������ turn�� �ٲ۴�
	networkManager::getInstance()->gameTurn = MSGList::n_turn;


	mAsioChatClient->postSend(false, sendPkt.nSize, (char*)&sendPkt);
	//scene��ȯ

}






void networkManager::disConnect()
{
	mAsioChatClient->closeConnect();
}







