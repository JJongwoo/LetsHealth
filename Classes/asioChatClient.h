#pragma once

#include <deque>
#include <iostream>
#include <boost\asio.hpp>
#include <boost\bind.hpp>
#include <boost\thread.hpp> //- cocos2d 스케줄러 이용하여 처리
#include "cocos2d.h"

#include "Protocol.h"

class asioChatClient
{
public:
	asioChatClient(boost::asio::io_service &ioServ);
	~asioChatClient();
	void run();
	void runIoServ();
	bool isConnecting();
	void loginOk();
	bool isLogin();
	void connect(boost::asio::ip::tcp::endpoint endpoint);
	void closeConnect();
	void postSend(const bool isConstantly, const int nSize, char *pData);
//private:
	void processPacket(const char *pData);
	void postReceive();
	void handle_connect(const boost::system::error_code &errCode);
	void handle_write(const boost::system::error_code &errCode, size_t bytes_transferred);
	void handle_receive(const boost::system::error_code &errCode, size_t bytes_transfered);
	std::deque<char*> mSendDataQue;

	boost::asio::io_service& mIoServ;
	boost::asio::ip::tcp::socket mSocket;


	std::array<char, 512> mRecvBuf;

	int mPktBufMaker;
	char mPktBuf[MAX_RECEIVE_BUFFER_LEN * 2];

	CRITICAL_SECTION mLock;
	

	bool mIsLogin;

};