#include "asioChatClient.h"
#include "networkManager.h"
#include "cocos2d.h"

using namespace std;




asioChatClient::asioChatClient(boost::asio::io_service & ioServ)
	:mIoServ(ioServ),
	mSocket(ioServ),
	mIsLogin(false)

{
	InitializeCriticalSectionAndSpinCount(&mLock, 4000);
}

asioChatClient::~asioChatClient()
{
	//임계구간
	EnterCriticalSection(&mLock);

	while (mSendDataQue.empty() == false)
	{
		delete[] mSendDataQue.front();
		mSendDataQue.pop_front();
	}

	LeaveCriticalSection(&mLock);
	DeleteCriticalSection(&mLock);
	//임계구간종료
}

bool asioChatClient::isConnecting()
{
	return mSocket.is_open();
}

void asioChatClient::loginOk()
{
	mIsLogin = true;
}

bool asioChatClient::isLogin()
{
	return mIsLogin;
}

void asioChatClient::connect(boost::asio::ip::tcp::endpoint endpoint)
{
	cocos2d::log("connect in ");
	mPktBufMaker = 0;
	//1번 문제 해결
	mSocket.async_connect(endpoint,
		boost::bind(&asioChatClient::handle_connect, this, boost::asio::placeholders::error)
	);


	cocos2d::log("connect out");
}

void asioChatClient::closeConnect()
{
	if (mSocket.is_open())
	{
		mSocket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
		//Sleep(500);
		//mSocket.close();
	}
}

void asioChatClient::postSend(const bool isConstantly, const int nSize, char * pData)
{
	cocos2d::log("postSend in");
	char *pSendData = nullptr;

	//임계구간
	EnterCriticalSection(&mLock);

	if (isConstantly == false)
	{
		cocos2d::log("mSendDataQue.push_back in");
		pSendData = new char[nSize];
		memcpy(pSendData, pData, nSize);
		mSendDataQue.push_back(pSendData);
	}
	else
	{
		pSendData = pData;
	}

	cocos2d::log("%d", mSendDataQue.size());
	if (isConstantly || mSendDataQue.size() < 5)
	{


		boost::asio::async_write(mSocket, boost::asio::buffer(pSendData, nSize),
			boost::bind(&asioChatClient::handle_write, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred)
		);
		/*
		if(mSendDataQue.size()>1){
		delete[] mSendDataQue.front();
		mSendDataQue.pop_front();
		}
		*/

	}
	cocos2d::log("postSend out");
	LeaveCriticalSection(&mLock);
	//임계구간 종료

}
void asioChatClient::postReceive()
{
	cocos2d::log("postReceive in");
	memset(&mRecvBuf, '\0', sizeof(mRecvBuf));
	mSocket.async_read_some(
		boost::asio::buffer(mRecvBuf),
		boost::bind(&asioChatClient::handle_receive, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred)
	);
	cocos2d::log("postReceive out");
}

void asioChatClient::handle_connect(const boost::system::error_code & errCode)
{
	cocos2d::log("handle_connect in");
	if (!errCode)
	{

		postReceive();
		//networkManager::getInstance()->succeedConnect();

		//auto schedule = cocos2d::Director::getInstance()->getScheduler();
		//schedule->performFunctionInCocosThread(CC_CALLBACK_0(asioChatClient::postReceive, this));



		//auto schedule = cocos2d::Director::getInstance()->getScheduler();
		//schedule->performFunctionInCocosThread(CC_CALLBACK_0(asioChatClient::runIoServ, this));
		//networkManager::getInstance()->succeedConnect();

		//접속성공 메세지
	}
	else
	{
		networkManager::getInstance()->failConnect();

		//접속실패 메세지
	}
	//cocos2d::log("handle_connect postReceive");
	//	postReceive();
	cocos2d::log("handle_connect out");
	networkManager::getInstance()->succeedConnect();
}

void asioChatClient::handle_write(const boost::system::error_code & errCode, size_t bytes_transferred)
{
	cocos2d::log("handle_write in");
	//임계구간 시작
	EnterCriticalSection(&mLock);
	cocos2d::log("%d", mSendDataQue.size());
	delete[] mSendDataQue.front();
	mSendDataQue.pop_front();
	cocos2d::log("%d", mSendDataQue.size());
	char *pData = nullptr;

	if (mSendDataQue.empty() == false)
	{
		pData = mSendDataQue.front();
	}

	LeaveCriticalSection(&mLock);
	//임계구간 종료

	if (pData != nullptr)
	{
		cocos2d::log("pData in");
		PACKET_HEADER *pHeader = (PACKET_HEADER*)pData;
		postSend(true, pHeader->nSize, pData);
	}
	cocos2d::log("handle_write out");
}


void asioChatClient::handle_receive(const boost::system::error_code & errCode, size_t bytes_transfered)
{

	cocos2d::log("handle_receive in");
	if (errCode)//에러코드 발생
	{
		cocos2d::log("handle_receive Error");
		if (errCode == boost::asio::error::eof)
		{
			cocos2d::log("handle_receive Error");
			//서버 연결이 끊어짐 메세지
		}
		else
		{
			cocos2d::log("Error");
			//에러메세지
		}

		closeConnect();
	}
	else        //에러코드 발생하지않음
	{
		cocos2d::log("handle_receive true in");
		memcpy(&mPktBuf[mPktBufMaker], mRecvBuf.data(), bytes_transfered);

		int nPktData = mPktBufMaker + bytes_transfered;
		int nReadData = 0;

		while (nPktData > 0)
		{
			if (nPktData < sizeof(PACKET_HEADER))
			{
				break;
			}

			PACKET_HEADER *pHeader = (PACKET_HEADER*)&mPktBuf[nReadData];

			if (pHeader->nSize <= nPktData)
			{
				cocos2d::log("dkdkdkdkdkdkdkdkdkdkdkdkdkdkdkdkdkdk");
				processPacket(&mPktBuf[nReadData]);

				nPktData -= pHeader->nSize;
				nReadData += pHeader->nSize;
			}
			else
			{
				break;
			}
		}

		if (nPktData > 0)
		{
			char tempBuf[MAX_RECEIVE_BUFFER_LEN] = { 0, };
			memcpy(&tempBuf[0], &mPktBuf[nReadData], nPktData);
			memcpy(&mPktBuf[0], &tempBuf[0], nPktData);
		}

		mPktBufMaker = nPktData;
		//cocos2d::log("cocosThread handle receive postReceive in");
		mIoServ.post(boost::bind(&asioChatClient::postReceive, this));
		//auto schedule = cocos2d::Director::getInstance()->getScheduler();
		//schedule->performFunctionInCocosThread(CC_CALLBACK_0(asioChatClient::postReceive, this));
		//postReceive();

	}
	cocos2d::log("handle_receive out");
}

void asioChatClient::processPacket(const char * pData)
{
	cocos2d::log("prcessPacket in");
	PACKET_HEADER* pHeader = (PACKET_HEADER*)pData;

	switch (pHeader->nID)
	{
	case RES_IN:
	{
		cocos2d::log("11111111111111111111111111111111111111111111");
		PKT_RES_IN* pPkt = (PKT_RES_IN*)pData;

		loginOk();

		//접속 성공여부 출력
	}
	break;
	case NOTICE_CHAT:
	{
		cocos2d::log("2222222222222222222222222222222222222222");
		PKT_NOTICE_CHAT* pPkt = (PKT_NOTICE_CHAT*)pData;

		//메세지 출력
	}
	break;

	case NOTICE_GAME:
	{
		cocos2d::log("five five five five");

		PKT_NOTICE_GAME* pPkt = (PKT_NOTICE_GAME*)pData;
		if (pPkt->gameResult == MSGList::gameLose)
			cout << "게임에서 졌습니다." << endl;
		else if(pPkt->gameResult == MSGList::gameWin)
			cout << "게임에서 이겼습니다." << endl;
		if (MSGList::gameStart == pPkt->gameStart)
		{

			cocos2d::log("%d", pPkt->gameStart);
			networkManager::getInstance()->gameStart = MSGList::gameStart;

		}
		else {
			cout << "gameStart false gameStart false gameStart false" << endl;
			cout << "networkManager::getInstance()->startGame : " << networkManager::getInstance()->gameStart << endl;
		}

		//게임 레디 여부 
	}
	break;
	case NOTICE_TURN:
	{
		cocos2d::log("six six six six");


		PKT_NOTICE_TURN* pPkt = (PKT_NOTICE_TURN*)pData;
		cout << "pPkt->gameTurn : " << pPkt->gameTurn << "pPkt->allReady" << pPkt->allReady << endl;
		networkManager::getInstance()->gameTurn = pPkt->gameTurn;
		cout << "나의 턴은 : " << networkManager::getInstance()->gameTurn << endl;

		//게임 턴 
	}
	break;


	default:
		break;
	}
}





