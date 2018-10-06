
#include"servo.h"


namespace interfaz {

	Servo::Servo(interfaz::Interfaz* _i, uint8_t _pin)
		: i(_i), pin(_pin) {
		//i->f->pinMode(pin, MODE_SERVO);
	}

	Servo::~Servo() {
	}


	void Servo::setPosition(uint8_t pos) {
		i->f->analogWriteExtended(pin, pos);
	}


}