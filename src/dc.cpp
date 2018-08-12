
#include"dc.h"


namespace interfaz {

	DC::DC(interfaz::Interfaz* _i, uint8_t _deviceNum, uint8_t _enable, uint8_t _in1, uint8_t _in2)
		: i(_i), deviceNum(_deviceNum), enable(_enable), in1(_in1), in2(_in2) {
			i->f->configDC(deviceNum, enable, in1, in2);
	}

	DC::~DC() {
	}


	void DC::turnOn() {
		i->f->DCturnOn(deviceNum);
	}

	void DC::turnOff() {
		i->f->DCturnOff(deviceNum);
	}

	void DC::brake() {
		i->f->DCbrake(deviceNum);
	}

	void DC::setDirection(uint8_t dir) {
		i->f->DCsetDir(deviceNum, dir);
	}

	void DC::setSpeed(uint8_t speed) {
		i->f->DCsetSpeed(deviceNum, speed);
	}

	void DC::inverse() {
		i->f->DCinverse(deviceNum);
	}


}