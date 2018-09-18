#pragma once
#pragma once

#include <iostream>
#include <boost\asio.hpp>
#include <boost\bind.hpp>
#include "asioChatClient.h"

class networkManager
{
public:
	//싱글턴으로 만듬
	static networkManager* getInstance();
	void succeedSend();
	void succeedReady();
	void succeedTurn();
	void succeedAllReady();
	void succeedFail();
	bool init();
	void connectServer(const char *pName, const char *pEndpoint);
	void failConnect();
	void succeedConnect();
	void disConnect();

	int gameReady;
	int gameStart;
	int gameTurn;
	int gameAllReady;
	int gameResult;

private:
	networkManager(); //싱글턴으로 하기 위해서 private 접근 지정자로 생성자 만듬
					  //~networkManager();
	void runIoServ();

	asioChatClient *mAsioChatClient;
	boost::asio::io_service *mIoServ;
	boost::asio::ip::tcp::endpoint mEndPoint;
	char mUserName[25];

	static networkManager* mInstance;//networkManager 싱글턴으로 만들기 위해 인스턴스 담음
};