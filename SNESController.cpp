

#include "SNESController.h"

SNESController::SNESController(uint8_t clock, uint8_t storbe, uint8_t data) : NESController(clock, storbe, data) {

}

SNESController::~SNESController() {

}

void SNESController::update() {
	digitalWrite(storbe, HIGH);
	delayMicroseconds(PAD_CLOCK);
	digitalWrite(storbe, LOW);

	buttons = 0;

	for (uint8_t i = 0; i < 16; i++)
		buttons |= read() << i;

	buttons = ~buttons;
}



bool SNESController::isB() {
	return buttons & 1;
}

bool SNESController::isY() {
	return buttons & 2;
}

bool SNESController::isA() {
	return buttons & 256;
}

bool SNESController::isX() {
	return buttons & 512;
}

bool SNESController::isL() {
	return buttons & 1024;
}

bool SNESController::isR() {
	return buttons & 2048;
}



void SNESController::setJoyStick() {
	joy.xAxis 	= AXIS_CENTER;
	joy.yAxis 	= AXIS_CENTER;

	joy.buttons = 0;

	if (isUp())
		joy.yAxis = AXIS_MIN;

	if (isDown())
		joy.yAxis = AXIS_MAX;

	if (isLeft())
		joy.xAxis = AXIS_MIN;

	if (isRight())
		joy.xAxis = AXIS_MAX;


	joy.buttons |= isA();
	joy.buttons |= isB() 	  << 1;
	joy.buttons |= isY()	  << 2;
	joy.buttons |= isX()	  << 3;
	joy.buttons |= isR()	  << 4;
	joy.buttons |= isL()	  << 5;
	joy.buttons |= isSelect() << 6;
	joy.buttons |= isStart()  << 7;

	Joystick.setState(&joy);

}
