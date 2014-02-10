
#ifndef NESCONTROLLER_H_
#define NESCONTROLLER_H_

#include <stdint.h>
#include "Arduino.h"
#include "USBAPI.h";

#define PAD_CLOCK 12

#define AXIS_MAX 255
#define AXIS_MIN 0
#define AXIS_CENTER 128

/**
 * Clase para leer el estado de un Pad de NES
 * y simular un Joystick USB
 */

class NESController {

protected:

	uint16_t buttons;
	JoyState_t joy;

	uint8_t storbe;
	uint8_t clock;
	uint8_t data;

	/**
	 * Leemos cada bit enviando por el mando
	 * y lo sincronizamos usando el CLOCK
	 */
	uint8_t read();

public:
	NESController(uint8_t clock, uint8_t storbe, uint8_t data);
	virtual ~NESController();
	virtual void update();


	/***************** BOTONES ***************/
	/* Los botones están guardados en los   **/
	/* bits de "buttons", usando potencias  **/
	/* de 2 vamos comprobando cada bit      **/
	/*****************************************/

	virtual bool isA(); 		//1
	virtual bool isB();			//2
	virtual bool isSelect();	//4
	virtual bool isStart();		//8
	virtual bool isUp();		//16
	virtual bool isDown();		//32
	virtual bool isLeft();		//64
	virtual bool isRight();		//128




	/**
	 * Una vez leido el estado del PAD, lo envíamos el
	 * PC usando el struct Joystick
	 */
	void setJoyStick();


	/**
	 * El Joystick en Arduino no se inicializa correctamente,
	 * deberemos ponerlo a MAX y después Centrados para evitar problemas
	 * hasta que no "cambian" de posición
	 */
	void initJoystick();


};

#endif
