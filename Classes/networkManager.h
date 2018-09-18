#pragma once
#pragma once

#include <iostream>
#include <boost\asio.hpp>
#include <boost\bind.hpp>
#include "asioChatClient.h"

class networkManager
{
public:
	//�̱������� ����
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
	networkManager(); //�̱������� �ϱ� ���ؼ� private ���� �����ڷ� ������ ����
					  //~networkManager();
	void runIoServ();

	asioChatClient *mAsioChatClient;
	boost::asio::io_service *mIoServ;
	boost::asio::ip::tcp::endpoint mEndPoint;
	char mUserName[25];

	static networkManager* mInstance;//networkManager �̱������� ����� ���� �ν��Ͻ� ����
};