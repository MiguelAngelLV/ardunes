ArduNES
=========
ArduNES es una librería encargada de leer los gamepads de NES y SNES desde un Arduino y simular un Joystick virtual en un PC.

Partiendo del códgio de [NESPad][1] he creado una librería más fácil de utilizar y con la posibilidad de no solo leer el pad, si no simular uno en PC.

Uso
====
Lo primero es copiar los archivos del carpeta core, _USBHID.cpp_ y _USBAPI.h_, en las librerías de arduino:

```bash
[carpeta de arduino]/hardware/arduino/cores/arduino
```
Después basta con crear una objeto del tipo NesController o SnesController indicando en que pines de Arduno están conectados el _storbe_, _clock_ y el _data_ y listo.

```c
#include "NintendoPads.h"
#include "SNESController.h"

#define CLOCK 	4
#define STORBE 	5
#define DATA    6

SNESController snes(CLOCK, STORBE, DATA);

void setup() {
    //Inicializamos el Joystick
	snes.initJoystick();
}

void loop(){
	//Leemos los datos del mando
	snes.update();
	//Actualizamos el joystick con
	//los datos leídos
	snes.setJoyStick();
}
```
Si queremos usralo solo para leer los datos del pad, podemos usar los métodos específicos para cada botón.

```c
#include "NESController.h"

#define CLOCK 	4
#define STORBE 	5
#define DATA    6

#define LED_A	10
#define LED_B	11

NESController nes(CLOCK, STORBE, DATA);


void setup() {
	pinMode(LED_A, OUTPUT);
	pinMode(LED_B, OUTPUT);
}

void loop(){

	nes.update();

	if (nes.isA())
		digitalWrite(LED_A, HIGH);
	else
		digitalWrite(LED_A, LOW);
	
	if (nes.isB())
		digitalWrite(LED_B, HIGH);
	else
		digitalWrite(LED_B, LOW);
		
}

```

PINS
======

NES
![NES](/nes.png "Pins de NES")
----------------------
SNES
![SNES](/nes.png "Pins de SNES")



  [1]: https://code.google.com/p/nespad/%20NESPad