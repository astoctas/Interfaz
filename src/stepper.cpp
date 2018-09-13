
#include"stepper.h"
#include <iostream>
#include <thread>
#include <functional>
using namespace std;

namespace interfaz {

	Stepper::Stepper(interfaz::Interfaz * _i, uint8_t _deviceNum, uint8_t _step, uint8_t _dir, uint8_t _enable, uint8_t _invert)
		: i(_i), deviceNum(_deviceNum), step(_step), dir(_dir),  enable(_enable), invertPins(_invert) {
		//setConfig();
	}

	Stepper::~Stepper() {
	}

	void Stepper::config(uint8_t _deviceNum, uint8_t _type, uint8_t _stepSize, uint8_t _stepOrMotor1Pin, uint8_t _dirOrMotor2Pin, uint8_t _enablePin, uint8_t _invertPins) {
		deviceNum = _deviceNum;
		type = _type;
		stepSize = _stepSize;
		step = _stepOrMotor1Pin;
		dir = _dirOrMotor2Pin;
		enable = _enablePin;
		invertPins = _invertPins;
		setConfig();
	}

	void Stepper::setConfig() {
		i->f->configStepper(deviceNum, type, stepSize, step, dir, enable, invertPins);
	}

	void Stepper::steps(uint16_t _steps) {
		int32_t steps = _steps;
		if (direction) steps = -1 * steps;
		status = 1;
		//setPins();
		i->f->enableOutputsStepper(deviceNum);
		i->f->stepStepper(deviceNum, steps);
	}

	void Stepper::finishCallback() {
		status = 0;
	}

	void Stepper::setDirection(uint8_t dir) {
		if (dir > 1) dir = 1;
		direction = dir;
	}

	void Stepper::setSpeed(double _speed) {
		speed = _speed;
		i->f->setSpeedStepper(deviceNum, speed);
	}

	void Stepper::invert() {
		direction = !direction;
	}

	void Stepper::stop() {
		i->f->stopStepper(deviceNum);
	}


}