# Let's Health
한성공학경진대회 출품작 (장려상 수상)

Cocos2d엔진과 OpenCV라이브러리 그리고 웹캠을 활용해 올바른 자세로 운동을 할 수 있도록 자세를 교정해주는 프로그램

opencv라이브러리중 컬러인식을 이용해 아령과 이용자의 관절 위치를 분석해 올바른 자세를 잡도록 지도

주요 코드는 classes폴더에 위치


-코드 

HelloWorldScene.cpp - 메인화면 (혼자하기, 같이하기, 환경설정, 나가기 버튼이 존재)
  
    ConfigScene.cpp - 운동강도와 아령색을 선택할 수 있는 환경설정 화면

    ModeSelectScene.cpp - 운동할 부위(팔운동과 어깨운동)를 선택하는 화면

      SoloPlayScene.cpp - 모드 선택에서 팔운동을 선택하면 나오는 운동화면, 웹캡 화면과 함께 나온다.

      ShoulderPlayScene.cpp - 모드 선택에서 어깨운동을 선택하면 나오는 운동화면, 웹캠 화면과 함께 나온다.

  
    WithPlayScene.cpp - 메인화면에서 같이하기를 누르면 나오는 화면이며 레디버튼을 누르면 현재 네트워크에 있는 다른 유저와 운동을 할 수 있다.

      MultiPlayScene.cpp - 멀티플레이시 운동화면이다.
    
    

Obje.cpp - OpenCV라이브러리의 컬러 인식기능을 이용해 객체(아령, 관절)를 구분할 수 있도록 만든 함수들이다.

networkManager.cpp, asiochatClient.cpp - 멀티플레이를 하기위해 필요한 함수들이다. boost asio 라이브러리를 활용했다.
