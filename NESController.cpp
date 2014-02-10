
#include "NESController.h"



NESController::NESController(uint8_t clock, uint8_t storbe, uint8_t data) {
	buttons			= 0;

	this->storbe 	= storbe;
	this->clock		= clock;
	this->data		= data;

	pinMode(data,   INPUT);
	pinMode(clock,  OUTPUT);
	pinMode(storbe, OUTPUT);

}

NESController::~NESController() {
}


void NESController::initJoystick() {

	memset(&joy, AXIS_MAX, sizeof(joy));
	Joystick.setState(&joy);

	delay(500);

	memset(&joy, AXIS_CENTER, sizeof(joy));
	joy.buttons  = 0;

	//Los Hat funcionan por grados, o algo así,
	//La única manera de ponerlos centrados es así
	joy.hatSw1 = 8;
	joy.hatSw2 = 8;

	Joystick.setState(&joy);

}


/**
 * Obtenemos el estado del PAD
 */
void NESController::update() {

	//Indicamos que vamos a comenzar
	//la lectura de datos usando el STORBE
	digitalWrite(storbe, HIGH);
	delayMicroseconds(PAD_CLOCK);
	digitalWrite(storbe, LOW);

	buttons = 0;

	//Leemos los 8 bits
	for (uint8_t i = 0; i < 8; i++)
		buttons |= read() << i;

	buttons = ~buttons;

}


uint8_t NESController::read() {
	uint8_t status = digitalRead(data);
	delayMicroseconds(PAD_CLOCK);
	digitalWrite(clock, HIGH);
	delayMicroseconds(PAD_CLOCK);
	digitalWrite(clock, LOW);
	return status;
}



void NESController::setJoyStick() {
	joy.xAxis 	= AXIS_CENTER;
	joy.yAxis 	= AXIS_CENTER;

	joy.buttons = 0;

	//Yo uso los ejes, pero podríamos
	//usar botones también

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
	joy.buttons |= isSelect() << 2;
	joy.buttons |= isStart()  << 3;

	Joystick.setState(&joy);

}




bool NESController::isA() {
	return buttons & 1;
}

bool NESController::isB() {
	return buttons & 2;
}

bool NESController::isSelect() {
	return buttons & 4;
}

bool NESController::isStart() {
	return buttons & 8;
}


bool NESController::isUp() {
	return buttons & 16;
}

bool NESController::isDown() {
	return buttons & 32;
}


bool NESController::isLeft() {
	return buttons & 64;
}

bool NESController::isRight() {
	return buttons & 128;
}

