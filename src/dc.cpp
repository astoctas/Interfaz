
#include"dc.h"


namespace interfaz {

	DC::DC(interfaz::Interfaz* _i,  uint8_t _deviceNum)
		: i(_i), deviceNum(_deviceNum) {

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