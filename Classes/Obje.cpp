#include "Obje.h"

Obje::Obje()
{
	//set values for default constructor
	setType("Obje");
	setColor(Scalar(0, 0, 0));

}

Obje::Obje(string name) {

	setType(name);

	if (name == "blue") {

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values

		setHSVmin(Scalar(92, 0, 0));
		setHSVmax(Scalar(124, 256, 256));

		//BGR value for Blue:
		setColor(Scalar(255, 0, 0));

	}

	if (name == "green") {

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values
	
	
		//¾ÆÄ§³ë Ä·
		//setHSVmin(Scalar(15, 60, 179));
		//setHSVmax(Scalar(42, 189, 256));

		//¾ÆÄ§Àç³ëÄ·
		setHSVmin(Scalar(19, 96, 136));
		setHSVmax(Scalar(57, 256, 256));
		
		//setHSVmin(Scalar(27, 68, 56));
		//setHSVmax(Scalar(54, 256, 256));

		//BGR value for Green:
		setColor(Scalar(0, 0, 255));
	}

	if (name == "yellow") {

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values

		setHSVmin(Scalar(14, 126, 129));
		setHSVmax(Scalar(55, 256, 256));

		//BGR value for Yellow:
		setColor(Scalar(0, 255, 255));
	}
	if (name == "red") {

		//TODO: use "calibration mode" to find HSV min
		//and HSV max values
		//setHSVmin(Scalar(150, 50, 110));
		//setHSVmax(Scalar(255, 255, 255));

		/*setHSVmin(Scalar(0, 94, 196));
		setHSVmax(Scalar(28, 255, 255));*/

		///sssss
		//setHSVmin(Scalar(32, 104, 15));
		//setHSVmax(Scalar(114, 237, 255));

		setHSVmin(Scalar(22, 52, 0));
		setHSVmax(Scalar(29, 237, 255));
		
		//setHSVmin(Scalar(87, 205, 85));
		//setHSVmax(Scalar(233, 255, 255));

		//setHSVmin(Scalar(0, 200, 0));
		//setHSVmax(Scalar(19, 255, 255));
		
		//BGR value for Red:
		setColor(Scalar(0, 255, 0));

	}
}

Obje::~Obje(void)
{
}

int Obje::getXPos() {

	return Obje::xPos;

}

void Obje::setXPos(int x) {

	Obje::xPos = x;

}

int Obje::getYPos() {

	return Obje::yPos;

}

void Obje::setYPos(int y) {

	Obje::yPos = y;

}

Scalar Obje::getHSVmin() {

	return Obje::HSVmin;

}
Scalar Obje::getHSVmax() {

	return Obje::HSVmax;
}

void Obje::setHSVmin(Scalar min) {

	Obje::HSVmin = min;
}


void Obje::setHSVmax(Scalar max) {

	Obje::HSVmax = max;
}