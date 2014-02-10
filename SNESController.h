
#ifndef SNESCONTROLLER_H_
#define SNESCONTROLLER_H_

#include "NESController.h"


/**
 * Clase para leer el estado de un Pad de NES
 * y simular un Joystick USB.
 *
 * Esta clase hereda de NESController. En ella
 * podéis encontrar los métodos faltantes y los comentarios.
 */

class SNESController : public NESController {
public:
	SNESController(uint8_t clock, uint8_t storbe, uint8_t data);
	virtual ~SNESController();


	virtual void update();


	virtual bool isB();			//1
	virtual bool isY();			//2
	virtual bool isA(); 		//256
	virtual bool isX();			//512
	virtual bool isL();			//1024
	virtual bool isR();			//2048

	void setJoyStick();
};

#endif
