

#pragma once 
#include <string>
#include "cocos2d.h"


//memset()명령어는 헤더로써 #include <string.h>가 필요하다.
//memset(시작 주소, 초기화할 값, 배열의 크기)

const unsigned short PORT_NUMBER = 31400;

const int MAX_RECEIVE_BUFFER_LEN = 512;
const int MAX_GAME_MESSAGE = 4;
const int MAX_NAME_LEN = 25;
const int MAX_MESSAGE_LEN = 129;

namespace MSGList {

	enum MSG_TYPE
	{
		fail,
		gameReady,
		n_gameReady,
		gameStart,
		n_gameStart,
		turn,
		n_turn,
		gameWin,
		gameLose
	};
}


struct PACKET_HEADER
{
	short nID;
	short nSize;
};



//  패킷
const short REQ_IN = 1;
// PKT_REQ_IN

const short RES_IN = 2;
// PKT_RES_IN

const short REQ_CHAT = 6;
// PKT_REQ_CHAT

const short NOTICE_CHAT = 7;
// PKT_NOTICE_CHAT

const short NOTICE_GAME = 8;
// PKT_NOTICE_GAME
const short NOTICE_TURN = 9;
// PKT_NOTICE_TURN



struct PKT_REQ_IN : public PACKET_HEADER //처음에 닉네임 받는거임
{
	void Init()
	{
		cocos2d::log("one one one one");
		nID = REQ_IN;
		nSize = sizeof(PKT_REQ_IN);
		memset(szName, 0, MAX_NAME_LEN);
	}

	char szName[MAX_NAME_LEN];
};

struct PKT_RES_IN : public PACKET_HEADER
{
	void Init()
	{
		cocos2d::log("two two two two");
		nID = RES_IN;
		nSize = sizeof(PKT_RES_IN);
		bIsSuccess = false;
	}

	bool bIsSuccess;
};

struct PKT_REQ_CHAT : public PACKET_HEADER
{
	void Init()
	{
		cocos2d::log("three three three three");
		nID = REQ_CHAT;
		nSize = sizeof(PKT_REQ_CHAT);
		memset(szMessage, 0, MAX_MESSAGE_LEN);
		park = 1;
	}
	int park;
	char szMessage[MAX_MESSAGE_LEN];
};

struct PKT_NOTICE_CHAT : public PACKET_HEADER
{
	void Init()
	{
		cocos2d::log("four four four four");
		nID = NOTICE_CHAT;
		nSize = sizeof(PKT_NOTICE_CHAT);
		memset(szName, 0, MAX_NAME_LEN);
		memset(szMessage, 0, MAX_MESSAGE_LEN);
	}

	char szName[MAX_NAME_LEN];
	char szMessage[MAX_MESSAGE_LEN];
};

struct PKT_NOTICE_GAME : public PACKET_HEADER
{
	void Init()
	{
		cocos2d::log("five five five five");
		nID = NOTICE_GAME;
		nSize = sizeof(PKT_NOTICE_GAME);
		memset(szName, 0, MAX_NAME_LEN);
		gameReady = MSGList::fail;
		gameStart = MSGList::fail;
		gameResult = MSGList::fail;


	}
	char szName[MAX_NAME_LEN];
	int gameReady;
	int gameStart;
	int gameResult;


};
struct PKT_NOTICE_TURN : public PACKET_HEADER
{
	void Init()
	{
		nID = NOTICE_TURN;
		nSize = sizeof(PKT_NOTICE_TURN);
		memset(szName, 0, MAX_NAME_LEN);
		gameTurn = MSGList::fail;
		allReady = MSGList::fail;
	}
	char szName[MAX_NAME_LEN];
	int gameTurn;
	int allReady;
};