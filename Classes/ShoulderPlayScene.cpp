#include "ShoulderPlayScene.h"
#include "audio/include/SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "Obje.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<time.h>
#include <thread>

#include <sstream>
#include <string>
#include "opencv\cv.h"
#include "opencv\highgui.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>

using namespace cv;
using namespace std;
using namespace CocosDenshion;
using namespace Shoulder;
USING_NS_CC;

#pragma comment(lib, "opencv_core2413.lib")
#pragma comment(lib, "opencv_imgproc2413.lib")
#pragma comment(lib, "opencv_highgui2413.lib")
#pragma comment(lib, "opencv_ml2413.lib")
#pragma comment(lib, "opencv_video2413.lib")
#pragma comment(lib, "opencv_features2d2413.lib")
#pragma comment(lib, "opencv_calib3d2413.lib")

/////���� ����
#define                                    PI                                                      3.141592
#define                                    RADIAN                                        ( PI / 180.0 )
#define                                    DEGREE                                       ( 180.0 / PI )
#define                                    RAD2DEG( Rad  )                    ( Rad * DEGREE )
#define                                    DEG2RAD( Degree )            ( Degree * RADIAN )
namespace Shoulder {

	int pre_count = 0;
	int set_count = 1;
	int work_count = 0;
	int countMax = (int)strtol(UserDefault::getInstance()->getStringForKey("ExerciseCount").c_str(), NULL, 10);
	int setMax = (int)strtol(UserDefault::getInstance()->getStringForKey("ExerciseSet").c_str(), NULL, 10);
	bool flag = TRUE;
	bool play_flag = TRUE;
	bool time_flag = true;
	bool startend_flag = true;
	bool guide_flag = true;
	bool fighting_flag = true;
	bool rest_flag = true;
	bool is_red = true;
	bool end_flag = false;
	int y = 1000, yy = -1;
	bool edu_flag = true;
	int gameCoin = 0;

	static time_t start;
	static time_t endd;
	static time_t end_time;
	static time_t start_time;

	int H_MIN = 0;
	int H_MAX = 256;
	int S_MIN = 0;
	int S_MAX = 256;
	int V_MIN = 0;
	int V_MAX = 256;
	//default capture width and height
	const int FRAME_WIDTH = 540;
	const int FRAME_HEIGHT = 960;
	//max number of objects to be detected in frame
	const int MAX_NUM_OBJECTS = 50;
	//minimum and maximum object area
	const int MIN_OBJECT_AREA = 25 * 25;
	const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH / 1.5;
	//names that will appear at the top of each window
	const string windowName = "Original Image";
	const string windowName1 = "HSV Image";
	const string windowName2 = "Thresholded Image";
	const string windowName3 = "After Morphological Operations";
	const string trackbarWindowName = "Trackbars";

	//The following for canny edge detec
	Mat dst, detected_edges;
	Mat src, src_gray;
	int edgeThresh = 1;
	int lowThreshold;
	int const max_lowThreshold = 100;
	int ratio = 3;
	int kernel_size = 3;
	int gok = 0;
	const char* window_name = "Edge Map";

	vector <Obje> shoulder_ready(vector <Obje> objects, Mat &cameraFeed);
	void shoulder_go(vector <Obje> objects, Mat &cameraFeed);


	void on_trackbar(int, void*)
	{//This function gets called whenever 
	 // trackbar position is changed

	}

	string intToString(int number) {

		std::stringstream ss;
		ss << number;
		return ss.str();
	}

	void createTrackbars() {
		//create window for trackbars
		namedWindow(trackbarWindowName, 0);
		//create memory to store trackbar name on window
		char TrackbarName[50];
		sprintf(TrackbarName, "H_MIN", H_MIN);
		sprintf(TrackbarName, "H_MAX", H_MAX);
		sprintf(TrackbarName, "S_MIN", S_MIN);
		sprintf(TrackbarName, "S_MAX", S_MAX);
		sprintf(TrackbarName, "V_MIN", V_MIN);
		sprintf(TrackbarName, "V_MAX", V_MAX);
		//create trackbars and insert them into window
		//3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
		//the max value the trackbar can move (eg. H_HIGH),
		//and the function that is called whenever the trackbar is moved(eg. on_trackbar)
		//                                  ---->    ---->     ---->
		createTrackbar("H_MIN", trackbarWindowName, &H_MIN, H_MAX, on_trackbar);
		createTrackbar("H_MAX", trackbarWindowName, &H_MAX, H_MAX, on_trackbar);
		createTrackbar("S_MIN", trackbarWindowName, &S_MIN, S_MAX, on_trackbar);
		createTrackbar("S_MAX", trackbarWindowName, &S_MAX, S_MAX, on_trackbar);
		createTrackbar("V_MIN", trackbarWindowName, &V_MIN, V_MAX, on_trackbar);
		createTrackbar("V_MAX", trackbarWindowName, &V_MAX, V_MAX, on_trackbar);
	}

	void drawObject(vector<Obje> theObjects, Mat &frame, Mat &temp, vector< vector<Point2i> > contours, vector<Vec4i> hierarchy) {

		if (play_flag == true) {
			for (int i = 0; i < theObjects.size(); i++) {

				//cv::putText(frame, intToString(theObjects.at(i).getXPos()) + " , " + intToString(theObjects.at(i).getYPos()), cv::Point(theObjects.at(i).getXPos(), theObjects.at(i).getYPos() + 20), 1, 1, theObjects.at(i).getColor());

				//if (flag == true)
					//cv::putText(frame, " Hands down ", cv::Point(5, 75), 1, 2.5, cv::Scalar(0, 0, 0), 2);
				//else
					//cv::putText(frame, " Hands up ", cv::Point(5, 75), 1, 2.5, cv::Scalar(0, 0, 0), 2);


				cv::drawContours(frame, contours, i, theObjects.at(i).getColor(), 3, 8, hierarchy);
				cv::circle(frame, cv::Point(theObjects.at(i).getXPos(), theObjects.at(i).getYPos()), 5, theObjects.at(i).getColor());
			}

			for (int i = 0; i < theObjects.size(); i++) {

				if (theObjects[i].getType() != "red") {
					is_red = false;
				}
				else
					is_red = true;

				if (play_flag == true && is_red == true) {
					if (theObjects.at(i).getYPos() >= y && gok < 80 && gok > 0 && gameCoin % 2 == 0)
					{
						if (flag == true) {
							flag = false;
							gameCoin++;
							if (gameCoin > 2)
							{
								work_count++;
							}
						}
					}
					
					else if (theObjects.at(i).getYPos() <= yy && gok > 120)
					{
						if (flag == false) {
							gameCoin++;
							flag = true;
						}
					}
				}

			}
			if (is_red != true) {
				shoulder_go(shoulder_ready(theObjects, frame), frame);

			}
		}
	}

	void drawObject(vector<Obje> theObjects, Mat &frame) {

		for (int i = 0; i < theObjects.size(); i++) {
			cv::circle(frame, cv::Point(theObjects.at(i).getXPos(), theObjects.at(i).getYPos()), 10, cv::Scalar(0, 0, 255));
		}
	}

	void morphOps(Mat &thresh) {

		//create structuring element that will be used to "dilate" and "erode" image.
		//the element chosen here is a 3px by 3px rectangle
		Mat erodeElement = getStructuringElement(MORPH_RECT, cv::Size(3, 3));
		//dilate with larger element so make sure object is nicely visible
		Mat dilateElement = getStructuringElement(MORPH_RECT, cv::Size(8, 8));

		erode(thresh, thresh, erodeElement);
		erode(thresh, thresh, erodeElement);

		dilate(thresh, thresh, dilateElement);
		dilate(thresh, thresh, dilateElement);
	}

	void trackFilteredObject(Mat threshold, Mat HSV, Mat &cameraFeed)
	{
		vector <Obje> objects;
		Mat temp;
		threshold.copyTo(temp);
		//these two vectors needed for output of findContours
		vector< vector<Point2i> > contours;
		vector<Vec4i> hierarchy;
		//find contours of filtered image using openCV findContours function
		findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
		//use moments method to find our filtered object
		double refArea = 0;
		bool objectFound = false;
		if (hierarchy.size() > 0) {
			int numObjects = hierarchy.size();
			//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
			if (numObjects < MAX_NUM_OBJECTS)
			{
				for (int index = 0; index >= 0; index = hierarchy[index][0])
				{
					Moments moment = moments((cv::Mat)contours[index]);
					double area = moment.m00;
					//if the area is less than 20 px by 20px then it is probably just noise
					//if the area is the same as the 3/2 of the image size, probably just a bad filter
					//we only want the object with the largest area so we safe a reference area each
					//iteration and compare it to the area in the next iteration.
					if (area > MIN_OBJECT_AREA)
					{

						Obje object;

						object.setXPos(moment.m10 / area);
						object.setYPos(moment.m01 / area);

						objects.push_back(object);

						objectFound = true;

					}
					else objectFound = false;
				}
				//let user know you found an object
				if (objectFound == true)
				{
					//draw object location on screen
					drawObject(objects, cameraFeed);
				}
			}
			else cv::putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", Point2i(0, 50), 1, 2, Scalar(0, 0, 255), 2);
		}
	}
	///���� ���ϱ�
	int GetAngleABC(Obje a, Obje b, Obje c)
	{
		Obje ab;
		ab.setXPos(b.getXPos() - a.getXPos());
		ab.setYPos(b.getYPos() - a.getYPos());
		Obje cb;
		cb.setXPos(b.getXPos() - c.getXPos());
		cb.setYPos(b.getYPos() - c.getYPos());

		float dot = (ab.getXPos() * cb.getXPos() + ab.getYPos() * cb.getYPos()); // dot product
		float cross = (ab.getXPos() * cb.getYPos() - ab.getYPos() * cb.getXPos()); // cross product

		float alpha = atan2(cross, dot);

		return (int)floor(alpha * 180.0 / CV_PI + 0.5);
	}
	// x��ǥ ����. ////���ȫ �ε�ȣ �ٲ�
	bool cmpx(Obje &a, Obje &b) {
		return a.getXPos() < b.getXPos();
	}
	// y��ǥ ����. ////���ȫ
	bool cmpy(Obje &a, Obje &b) {
		return a.getYPos() < b.getYPos();
	}

	vector <Obje> shoulder_ready(vector <Obje> objects, Mat &cameraFeed) {

		if (edu_flag == true) {
			gok = 0;
			///�� ����!
			if (objects.size() == 3) {

				sort(objects.begin(), objects.end(), cmpy);
				/////�ȱ������� �������
				if (yy != -1) {
					//line(cameraFeed, cv::Point(objects[0].getXPos(), 0), cv::Point(objects[0].getXPos(), objects[0].getYPos()), Scalar(0, 255, 0), 2);

					//FM �� �ڼ�
					if (objects[1].getXPos() > objects[2].getXPos() && objects[1].getXPos() > objects[0].getXPos()) {
						Obje forth;
						forth.setXPos(objects[1].getXPos());
						forth.setYPos(objects[2].getYPos());

						//line(cameraFeed, cv::Point(forth.getXPos(), forth.getYPos()), cv::Point(objects[2].getXPos(), objects[2].getYPos()), Scalar(0, 0, 255), 2);
						//line(cameraFeed, cv::Point(objects[2].getXPos(), objects[2].getYPos()), cv::Point(objects[0].getXPos(), objects[0].getYPos()), Scalar(0, 255, 0), 2);

						gok = GetAngleABC(forth, objects[2], objects[0]);

						if (gok < 0)
							gok = abs(gok);

						if (gok >= 80 && gok < 130) {
							clock_t end = time(NULL);
							if (time_flag) {
								start = time(NULL);
								time_flag = false;
							}

							//cv::putText(cameraFeed, "timer : " + intToString(end - start), cv::Point(5, 150), 1, 2.5, cv::Scalar(0, 0, 0), 2);

							if ((end - start) > 3) {

								time_flag = true;
								y = objects[0].getYPos() - 70;
								edu_flag = false;
							}
						}
						else
							time_flag = true;

					}

					//���� �ʹ� �������
					else if (objects[2].getXPos() > objects[1].getXPos() && objects[2].getXPos() > objects[0].getXPos()) {

						//line(cameraFeed, cv::Point(objects[0].getXPos(), objects[0].getYPos()), cv::Point(objects[1].getXPos(), objects[1].getYPos()), Scalar(0, 0, 255), 2);
						//line(cameraFeed, cv::Point(objects[1].getXPos(), objects[1].getYPos()), cv::Point(objects[2].getXPos(), objects[2].getYPos()), Scalar(0, 255, 0), 2);

						gok = GetAngleABC(objects[0], objects[1], objects[2]);

						if (gok < 0)
							gok = abs(gok);


						if (gok >= 40 && gok < 115) {
							clock_t end = time(NULL);
							if (time_flag) {
								start = time(NULL);
								time_flag = false;
							}

							//cv::putText(cameraFeed, "timer : " + intToString(end - start), cv::Point(5, 150), 1, 2.5, cv::Scalar(0, 0, 0), 2);

							if ((end - start) > 3) {
								edu_flag = false;
								time_flag = true;
								y = objects[0].getYPos() - 70;

							}
						}
						else
							time_flag = true;
					}
					else
						time_flag = true;
				}

				//////////////�ȵ�� �غ�
				else {

					if (yy == -1 && objects[1].getYPos() < y && objects[0].getXPos() > objects[1].getXPos()) {

						//line(cameraFeed, cv::Point(objects[0].getXPos(), objects[0].getYPos()), cv::Point(objects[1].getXPos(), objects[1].getYPos()), Scalar(0, 0, 255), 2);
						//line(cameraFeed, cv::Point(objects[1].getXPos(), objects[1].getYPos()), cv::Point(objects[2].getXPos(), objects[2].getYPos()), Scalar(0, 100, 0), 2);

						gok = GetAngleABC(objects[0], objects[1], objects[2]);

						if (gok < 0)
							gok = abs(gok);

						if (gok > 110) {
							clock_t eend = time(NULL);
							if (time_flag) {
								start = time(NULL);
								time_flag = false;
							}
							//cv::putText(cameraFeed, "timer : " + intToString(eend - start), cv::Point(5, 150), 1, 2.5, cv::Scalar(0, 0, 0), 2);

							if ((eend - start) > 3) {

								if (yy == -1) {
									yy = objects[0].getYPos() - 30;
								}
								time_flag = true;


							}
						}
						else
							time_flag = true;
					}
					else
						time_flag = true;
				}
				cv::putText(cameraFeed, "angle : " + intToString(gok), cv::Point(5, 100), 1, 2.5, cv::Scalar(0, 0, 0), 2);
			}
			else
				time_flag = true;
		}
		return objects;
	}
	
	void shoulder_go(vector <Obje> objects, Mat &cameraFeed) {
		///�� ����!
		if (edu_flag == false) {
			if (objects.size() == 3) {

				sort(objects.begin(), objects.end(), cmpy);

				//line(cameraFeed, cv::Point(objects[0].getXPos(), objects[0].getYPos()), cv::Point(objects[1].getXPos(), objects[1].getYPos()), Scalar(0, 0, 255), 2);
				//line(cameraFeed, cv::Point(objects[1].getXPos(), objects[1].getYPos()), cv::Point(objects[2].getXPos(), objects[2].getYPos()), Scalar(0, 255, 0), 2);

				////x�� ���� ����
				gok = GetAngleABC(objects[0], objects[1], objects[2]);
				// ���ȭ
				if (gok < 0)
					gok = abs(gok);


				cv::putText(cameraFeed, "angle : " + intToString(gok), cv::Point(5, 100), 1, 2.5, cv::Scalar(0, 0, 0), 2);
			}
		}
	}


	void trackFilteredObject(Obje theObject, Mat threshold, Mat HSV, Mat &cameraFeed) {

		vector <Obje> objects;
		Mat temp;
		threshold.copyTo(temp);
		//these two vectors needed for output of findContours
		vector<vector<Point2i> > contours;
		vector<Vec4i> hierarchy;
		//find contours of filtered image using openCV findContours function
		findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
		//use moments method to find our filtered object
		double refArea = 0;
		bool objectFound = false;

		if (hierarchy.size() > 0) {
			int numObjects = hierarchy.size();
			//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
			if (numObjects < MAX_NUM_OBJECTS) {
				for (int index = 0; index >= 0; index = hierarchy[index][0]) {

					Moments moment = moments((cv::Mat)contours[index]);
					double area = moment.m00;

					//if the area is less than 20 px by 20px then it is probably just noise
					//if the area is the same as the 3/2 of the image size, probably just a bad filter
					//we only want the object with the largest area so we safe a reference area each
					//iteration and compare it to the area in the next iteration.
					if (area > MIN_OBJECT_AREA) {

						Obje object;

						object.setXPos(moment.m10 / area);
						object.setYPos(moment.m01 / area);
						object.setType(theObject.getType());
						object.setColor(theObject.getColor());

						objects.push_back(object);
						objectFound = true;


						///�� ����!
						//edu_go(edu_ready(objects, cameraFeed), cameraFeed);
					}
					else objectFound = false;
				}
				//let user know you found an object
				if (objectFound == true) {
					//draw object location on screen
					drawObject(objects, cameraFeed, temp, contours, hierarchy);
				}

			}
			//else cv::putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", Point2i(0, 50), 1, 2, Scalar(0, 0, 255), 2);
		}
	}



	Scene* ShoulderPlayScene::createScene()
	{
		auto scene = Scene::create();

		auto layer = ShoulderPlayScene::create();

		scene->addChild(layer);

		return scene;
	}

	bool ShoulderPlayScene::init()
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

		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		edu_flag = true;
		interval_flag = false;
		time_flag = true;

		thread thread_name(ShoulderPlayScene::videoInput);
		thread_name.detach();


		TTFConfig ttfConfig("fonts/arial.ttf", 68, GlyphCollection::DYNAMIC, nullptr, true);
		SetScore = cocos2d::Sprite::create("Images/Setscore.png");
		CountScore = cocos2d::Sprite::create("Images/CountScore.png");

		SetScore->setPosition(Vec2(visibleSize.width*0.1, visibleSize.height*0.2));
		SetScore->setLocalZOrder(2);
		SetScore->setScale(0.8f);
		SetScore->setAnchorPoint(Vec2(0, 0));
		this->addChild(SetScore);

		CountScore->setPosition(Vec2(visibleSize.width*0.04, visibleSize.height*0.1));
		CountScore->setLocalZOrder(2);
		CountScore->setScale(0.8f);
		CountScore->setAnchorPoint(Vec2(0, 0));
		this->addChild(CountScore);


		SetLabel = Label::createWithTTF(ttfConfig, "a", TextHAlignment::LEFT);
		CountLabel = Label::createWithTTF(ttfConfig, "a", TextHAlignment::LEFT);

		SetLabel->setString(intToString(work_count) + " / " + UserDefault::getInstance()->getStringForKey("ExerciseSet").c_str());
		SetLabel->setLocalZOrder(2);
		SetLabel->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.2));
		SetLabel->setColor(Color3B::WHITE);
		SetLabel->setAnchorPoint(Vec2(0, 0));
		SetLabel->enableOutline(Color4B::BLACK, 3);
		SetLabel->enableShadow(Color4B::BLACK, cocos2d::Size(3, -4));
		this->addChild(SetLabel);

		CountLabel->setString(intToString(set_count) + " / " + UserDefault::getInstance()->getStringForKey("ExerciseCount").c_str());
		CountLabel->setLocalZOrder(2);
		CountLabel->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.09));
		CountLabel->setColor(Color3B::WHITE);
		CountLabel->setAnchorPoint(Vec2(0, 0));
		CountLabel->enableOutline(Color4B::BLACK, 3);
		CountLabel->enableShadow(Color4B::BLACK, cocos2d::Size(3, -4));
		this->addChild(CountLabel);

		GuideSprite = cocos2d::Sprite::create("Images/GuidePosition.png");
		GuideSprite->setPosition(Vec2(visibleSize.width*0.45, visibleSize.height*0.5));
		GuideSprite->setScale(0.8f);
		GuideSprite->setAnchorPoint(Vec2(0, 0));

		this->addChild(GuideSprite);

		ReadySprite = cocos2d::Sprite::create("Images/ReadyCount3.png");
		ReadySprite->setPosition(Vec2(visibleSize.width*0.78, visibleSize.height*0.67));
		ReadySprite->setAnchorPoint(Vec2(0.5, 0.5));
		ReadySprite->setVisible(false);
		this->addChild(ReadySprite);

		FightingSprite = cocos2d::Sprite::create("Images/Fighting.png");
		FightingSprite->setPosition(Vec2(visibleSize.width*0.45, visibleSize.height*0.3));
		FightingSprite->setScale(0.8f);
		FightingSprite->setAnchorPoint(Vec2(0, 0));
		FightingSprite->setLocalZOrder(10);
		FightingSprite->setVisible(false);
		this->addChild(FightingSprite);


		auto item1 = MenuItemImage::create(
			"Images/ToMain.png", "Images/ToMain1.png",
			CC_CALLBACK_1(ShoulderPlayScene::doClose, this));


		pMenu = Menu::create(item1, nullptr);
		pMenu->setAnchorPoint(Vec2(0, 0));
		pMenu->alignItemsVertically();
		pMenu->alignItemsVerticallyWithPadding(250);
		pMenu->setScale(0.85f);
		pMenu->setPosition(Vec2(visibleSize.width*0.8, visibleSize.height*0.2));
		this->addChild(pMenu);

		ModelSprite = Sprite::create("Images/BodyMeling27.png");
		ModelSprite->setPosition(Vec2(visibleSize.width*0.25, visibleSize.height*0.65));
		ModelSprite->setAnchorPoint(Vec2(0.5, 0.5));
		this->addChild(ModelSprite);

		RestTimeSprite = Sprite::create("Images/RestTime1.png");
		RestTimeSprite->setScale(0.6f);
		RestTimeSprite->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.65));
		RestTimeSprite->setAnchorPoint(Vec2(0, 0));
		RestTimeSprite->setVisible(false);
		this->addChild(RestTimeSprite);


		UpdownSprite = Sprite::create("Images/UP.png");
		UpdownSprite->setPosition(Vec2(visibleSize.width*0.7, visibleSize.height*0.8));
		UpdownSprite->setAnchorPoint(Vec2(0.5, 0));
		UpdownSprite->setVisible(false);
		this->addChild(UpdownSprite);


		auto action = Sequence::create(
			RotateBy::create(0.5, 8),
			RotateBy::create(0.5, -8),
			RotateBy::create(0.5, -8),
			RotateBy::create(0.5, 8),
			RotateBy::create(1.5, 0),
			nullptr);
		auto rep = RepeatForever::create(action);
		UpdownSprite->runAction(rep);

		EndSprite = Sprite::create("Images/GuideEnd.png");
		EndSprite->setAnchorPoint(Vec2(0.5, 0.5));
		EndSprite->setPosition(Vec2(visibleSize.width*0.7, visibleSize.height*0.65));
		EndSprite->setScale(0.8f);
		EndSprite->setVisible(false);
		this->addChild(EndSprite);

		this->scheduleUpdate();
		return true;
	}

	void ShoulderPlayScene::doClose(Ref* pSender)
	{
		auto pScene = HelloWorld::createScene();
		Director::getInstance()->replaceScene(pScene);
	}

	void ShoulderPlayScene::doRecall(Ref* pSender)
	{
		auto pScene = ShoulderPlayScene::createScene();
		Director::getInstance()->replaceScene(pScene);
	}

	void ShoulderPlayScene::update(float dt) {

		if (interval_flag == false) {
			start_interval = time(NULL);
		}

		if (play_flag == true && edu_flag == false) {

			
			if (gok < 124 && gok >= 120) {
				ModelSprite->setTexture("Images/BodyMeling25.png");
			}
			else if (gok < 120 && gok >= 118) {
				ModelSprite->setTexture("Images/BodyMeling24.png");
			}
			else if (gok < 118 && gok >= 116) {
				ModelSprite->setTexture("Images/BodyMeling23.png");
			}
			else if (gok < 116 && gok >= 114) {
				ModelSprite->setTexture("Images/BodyMeling22.png");
			}
			else if (gok < 114 && gok >= 112) {
				ModelSprite->setTexture("Images/BodyMeling21.png");
			}
			else if (gok < 112 && gok >= 110) {
				ModelSprite->setTexture("Images/BodyMeling20.png");
			}
			else if (gok < 110 && gok >= 108) {
				ModelSprite->setTexture("Images/BodyMeling19.png");
			}
			else if (gok < 108 & gok >= 106) {
				ModelSprite->setTexture("Images/BodyMeling18.png");
			}
			else if (gok < 106 && gok >= 104) {
				ModelSprite->setTexture("Images/BodyMeling17.png");
			}
			else if (gok < 104 && gok >= 102) {
				ModelSprite->setTexture("Images/BodyMeling16.png");
			}
			else if (gok < 102 && gok >= 100) {
				ModelSprite->setTexture("Images/BodyMeling15.png");
			}
			else if (gok < 100 && gok >= 98) {
				ModelSprite->setTexture("Images/BodyMeling14.png");
			}
			else if (gok < 98 && gok >= 96) {
				ModelSprite->setTexture("Images/BodyMeling13.png");
			}
			else if (gok < 96 && gok >= 94) {
				ModelSprite->setTexture("Images/BodyMeling12.png");
			}
			else if (gok < 94 && gok >= 92) {
				ModelSprite->setTexture("Images/BodyMeling11.png");
			}
			else if (gok < 92 && gok >= 90) {
				ModelSprite->setTexture("Images/BodyMeling10.png");
			}
			else if (gok < 90 && gok >= 88) {
				ModelSprite->setTexture("Images/BodyMeling9.png");
			}
			else if (gok < 88 && gok >= 86) {
				ModelSprite->setTexture("Images/BodyMeling8.png");
			}
			else if (gok < 86 && gok >= 84) {
				ModelSprite->setTexture("Images/BodyMeling7.png");
			}
			else if (gok < 84 && gok >= 82) {
				ModelSprite->setTexture("Images/BodyMeling6.png");
			}
			else if (gok < 82 && gok >= 80) {
				ModelSprite->setTexture("Images/BodyMeling5.png");
			}
			else if (gok < 80 && gok >= 78) {
				ModelSprite->setTexture("Images/BodyMeling4.png");
			}
			else if (gok < 78 && gok >= 76) {
				ModelSprite->setTexture("Images/BodyMeling3.png");
			}
			

		}


		if (set_count <= (int)strtol(UserDefault::getInstance()->getStringForKey("ExerciseSet").c_str(), NULL, 10) && play_flag == true) {
			SetLabel->setString(intToString(set_count) + " / " + UserDefault::getInstance()->getStringForKey("ExerciseSet").c_str());
		}
		if (work_count <= (int)strtol(UserDefault::getInstance()->getStringForKey("ExerciseCount").c_str(), NULL, 10) && play_flag == true) {
			CountLabel->setString(intToString(work_count) + " / " + UserDefault::getInstance()->getStringForKey("ExerciseCount").c_str());
		}
		if (set_count == setMax && work_count == countMax)
		{
			end_time = time(NULL);
			if (end_flag == false) {
				start_time = time(NULL);
				EndSprite->setVisible(true);
				auto EndFadeOut = FadeOut::create(0);
				auto EndFadeIn = FadeIn::create(2.5);
				auto EndSeq = Sequence::create(EndFadeOut, EndFadeIn, nullptr);
				EndSprite->runAction(EndSeq);
				end_flag = true;
			}

			if ((int)end_time - (int)start_time == 5) {
				ShoulderPlayScene::doClose(this);
			}
			UpdownSprite->setVisible(false);
			play_flag = false;
		}
		else if (work_count == countMax) {
			work_count = 0;
			pre_count = 0;
			fighting_flag = false;
			play_flag = false;
			////���ȫ
			edu_flag = true;
			time_flag = true;
			interval_flag = true;
			guide_flag = true;
		}

		if (interval_flag == true) {
			end_interval = time(NULL);
			GuideSprite->setVisible(false);

			if (rest_flag == true) {
				RestTimeSprite->setVisible(true);
				UpdownSprite->setVisible(false);
				auto RestAnimation = Animation::create();
				RestAnimation->setDelayPerUnit(0.4f);
				RestAnimation->addSpriteFrameWithFile("Images/RestTime1.png");
				RestAnimation->addSpriteFrameWithFile("Images/RestTime2.png");
				RestAnimation->addSpriteFrameWithFile("Images/RestTime3.png");
				RestAnimation->addSpriteFrameWithFile("Images/RestTime4.png");

				auto RestAnimate = Animate::create(RestAnimation);
				auto RestRepeat = RepeatForever::create(RestAnimate);

				RestTimeSprite->runAction(RestRepeat);
				rest_flag = false;

			}



			if ((int)end_interval - (int)start_interval == atoi(UserDefault::getInstance()->getStringForKey("ExerciseInterval").c_str())) {
				play_flag = true;
				rest_flag = true;
				interval_flag = false;
				RestTimeSprite->stopAllActions();
				RestTimeSprite->setVisible(false);
				set_count++;
			}
			y = 1000;
			yy = -1;

		}


		if (guide_flag == true && time_flag == true && interval_flag == false) {

			GuideSprite->setVisible(true);//setYourPosition
			ReadySprite->setVisible(false);
			ReadySprite->stopAllActions();
			GuideSprite->setTexture("Images/GuidePosition.png");
			auto guideFadeOut = FadeOut::create(0.8);
			auto guideFadeIn = FadeIn::create(0.6);
			auto guideseq = Sequence::create(guideFadeOut, guideFadeIn, nullptr);
			auto repeatGuide = RepeatForever::create(guideseq);
			GuideSprite->runAction(repeatGuide);
			guide_flag = false;
		}
		else if (time_flag == false && guide_flag == false && (gok >= 115 && gok < 180) && edu_flag == true)
		{

			GuideSprite->setVisible(false);
			ReadySprite->setVisible(true);
			GuideSprite->stopAllActions();

			auto animation = Animation::create();
			animation->setDelayPerUnit(1.0f);
			animation->addSpriteFrameWithFile("Images/ReadyCount3.png");
			animation->addSpriteFrameWithFile("Images/ReadyCount2.png");
			animation->addSpriteFrameWithFile("Images/ReadyCount1.png");
			auto animate = Animate::create(animation);

			ReadySprite->runAction(animate);
			auto guideScaleBys = ScaleTo::create(0, 0);
			auto guideScaleBye = ScaleTo::create(1, 1);
			auto readyseq = Sequence::create(guideScaleBys, guideScaleBye, nullptr);
			auto repeatGuidec = Repeat::create(readyseq, 3);
			//GuideSprite->runAction(repeatGuidec);
			ReadySprite->runAction(repeatGuidec);
			guide_flag = true;
		}

		else if (time_flag == false && guide_flag == false && (gok >= 100 && gok < 130) && y == 1000)
		{
			log("%d", gok);
			GuideSprite->setVisible(false);//3   2    1
			ReadySprite->setVisible(true);
			GuideSprite->stopAllActions();

			auto animation = Animation::create();
			animation->setDelayPerUnit(1.0f);
			animation->addSpriteFrameWithFile("Images/ReadyCount3.png");
			animation->addSpriteFrameWithFile("Images/ReadyCount2.png");
			animation->addSpriteFrameWithFile("Images/ReadyCount1.png");
			auto animate = Animate::create(animation);

			ReadySprite->runAction(animate);
			auto guideScaleBys = ScaleTo::create(0, 0);
			auto guideScaleBye = ScaleTo::create(1, 1);
			auto readyseq = Sequence::create(guideScaleBys, guideScaleBye, nullptr);
			auto repeatGuidec = Repeat::create(readyseq, 3);
			//GuideSprite->runAction(repeatGuidec);
			ReadySprite->runAction(repeatGuidec);
			guide_flag = true;
		}


		if (edu_flag == false) {
			if (play_flag == true) {
				UpdownSprite->setVisible(true);
			}
			ReadySprite->setVisible(false);
			GuideSprite->setVisible(false);

			if (flag == true) {
				UpdownSprite->setTexture("Images/DOWN.png");
			}
			else if (flag == false) {
				UpdownSprite->setTexture("Images/UP.png");
			}
		}
		else if (edu_flag == true) {
			if(yy!=-1)
				ModelSprite->setTexture("Images/BodyMeling1.png");
			else
				ModelSprite->setTexture("Images/BodyMeling27.png");
		}

		if (pre_count != work_count) {

			auto visibleSize = Director::getInstance()->getVisibleSize();
			FightingSprite->stopAllActions();
			FightingSprite->setPosition(Vec2(visibleSize.width*0.45, visibleSize.height*0.5));
			auto fightingFadeIn = FadeIn::create(0);
			auto fightingJumpBy = JumpBy::create(0.3, Vec2(0, 50), 50, 1);
			auto fightingFadeOut = FadeOut::create(0.3);
			auto fightingseq = Sequence::create(fightingFadeIn, fightingJumpBy, fightingFadeOut, nullptr);
			FightingSprite->setVisible(true);
			FightingSprite->runAction(fightingseq);
			pre_count = work_count;

		}
		


	}


	void ShoulderPlayScene::videoInput()
	{
		//if we would like to calibrate our filter values, set to true.
		//bool calibrationMode = false;
		bool calibrationMode = false;

		//Matrix to store each frame of the webcam feed
		Mat cameraFeed;
		Mat threshold;
		Mat HSV;
		Mat lr;

		string ret = UserDefault::getInstance()->getStringForKey("ColorInfo");
		string Colorinfo = ret.c_str();
		if (calibrationMode) {
			//create slider bars for HSV filtering
			createTrackbars();
		}

		//video capture object to acquire webcam feed
		namedWindow("background window", WINDOW_NORMAL);
		//setWindowProperty("background window", WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
		VideoCapture capture(1);

		//open capture object at location zero (default location for webcam)
		capture.open(0);
		//set height and width of capture frame
		capture.set(CV_CAP_PROP_FRAME_WIDTH, 1000);
		capture.set(CV_CAP_PROP_FRAME_HEIGHT, 1000);
		//start an infinite loop where webcam feed is copied to cameraFeed matrix
		//all of our operations will be performed within this loop
		waitKey(1000);
		//flip(capture, capture, 1);
		pre_count = 0;
		work_count = 0;
		set_count = 1;
		gameCoin = 0;
		y = 1000, yy = -1;
		play_flag = true;
		fighting_flag = false;
		end_flag = false;

		while (1) {

			capture.read(cameraFeed);

			src = cameraFeed;

			//line(cameraFeed, cv::Point(0, y), cv::Point(640, y), Scalar(0, 255, 0), 2);
			//line(cameraFeed, cv::Point(0, yy), cv::Point(640, yy), Scalar(0, 255, 0), 2);

			flip(cameraFeed, src, 1);
			if (!src.data)
			{
				//return -1;
				break;
			}
			//cv::putText(src, "Count : " + intToString(work_count), cv::Point(10, 30), 1, 2.5, cv::Scalar(0, 0, 0), 2);
			//convert frame from BGR to HSV colorspace
			cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);

			if (calibrationMode == true) {

				//need to find the appropriate color range values
				// calibrationMode must be false

				//if in calibration mode, we track objects based on the HSV slider values.
				cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
				inRange(HSV, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold);
				morphOps(threshold);
				//imshow(windowName2, threshold);

				//the folowing for canny edge detec
				/// Create a matrix of the same type and size as src (for dst)
				dst.create(src.size(), src.type());
				/// Convert the image to grayscale
				cvtColor(src, src_gray, CV_BGR2GRAY);
				/// Create a window
				namedWindow(window_name, CV_WINDOW_AUTOSIZE);

				/// Create a Trackbar for user to enter threshold
				createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold);
				/// Show the image
				//trackFilteredObject(threshold, HSV, cameraFeed);
				//trackFilteredObject_angle(threshold, HSV, cameraFeed);
			}
			else {
				//create some temp fruit objects so that
				//we can use their member functions/information

				Obje red("red"), angle("yellow");
				if (Colorinfo == "purple") {
					red.setHSVmin(Scalar(134, 155, 107));
					red.setHSVmax(Scalar(155, 224, 150));
				}
				else if (Colorinfo == "green") {
					//red.setHSVmax(Scalar(104, 256, 256))
					red.setHSVmin(Scalar(60, 115, 45));
					red.setHSVmax(Scalar(92, 236, 212));
				}

				//then reds
				cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
				inRange(HSV, red.getHSVmin(), red.getHSVmax(), threshold);
				morphOps(threshold);
				trackFilteredObject(red, threshold, HSV, cameraFeed);


				cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
				inRange(HSV, angle.getHSVmin(), angle.getHSVmax(), threshold);
				morphOps(threshold);
				trackFilteredObject(angle, threshold, HSV, cameraFeed);

			}
			//show frames
			//imshow(windowName2,threshold);

			//imshow(windowName, cameraFeed);
			imshow("background window", cameraFeed);

			//imshow(windowName1,HSV);

			//delay 30ms so that screen can refresh.
			//image will not appear without this waitKey() command

			if (set_count == setMax && work_count == countMax) {
				cv::destroyWindow("background window");
				break;
			}

			if (waitKey(1) == 27) {
				cv::destroyWindow("background window");
				break;
			}
		}
	}
}