#include "NintendoPads.h"
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
