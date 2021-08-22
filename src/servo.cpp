
#include"servo.h"


namespace interfaz {

	Servo::Servo(interfaz::Interfaz* _i, uint8_t _deviceNum)
		: i(_i), deviceNum(_deviceNum) {
		//i->f->servoAttach(deviceNum);
		//i->f->pinMode(pin, MODE_SERVO);
	}

	Servo::~Servo() {
	}


	void Servo::setPosition(uint8_t pos) {
		i->f->servoWrite(deviceNum, pos);
	}


}