
#include"stepper.h"
#include <iostream>
#include <thread>
#include <functional>
using namespace std;

namespace interfaz {

	Stepper::Stepper(interfaz::Interfaz * _i, uint8_t _deviceNum, uint8_t _enable1, uint8_t _enable2, uint8_t _in1, uint8_t _in2, uint8_t _in3, uint8_t _in4)
		: i(_i), deviceNum(_deviceNum), enable1(_enable1), enable2(_enable2), in1(_in1), in2(_in2), in3(_in3), in4(_in4) {
		setConfig();
	}

	Stepper::~Stepper() {
	}

	void Stepper::setPins() {
		i->setPin(enable1, MODE_PWM);
		i->setPin(enable2, MODE_PWM);
		i->setPin(in1, MODE_STEPPER);
		i->setPin(in2, MODE_STEPPER);
		i->setPin(in3, MODE_STEPPER);
		i->setPin(in4, MODE_STEPPER);
	}

	void Stepper::config(uint8_t _deviceNum, uint8_t _type, uint8_t _stepSize, uint8_t _dirOrMotor1Pin, uint8_t _dirOrMotor2Pin, uint8_t _motorPin3, uint8_t _motorPin4, uint8_t enablePin) {
		deviceNum = _deviceNum;
		type = _type;
		stepSize = _stepSize;
		in1 = _dirOrMotor1Pin;
		in2 = _dirOrMotor2Pin;
		in3 = _motorPin3;
		in4 = _motorPin4;
		setConfig();
	}

	void Stepper::setConfig() {
		i->f->configStepper(deviceNum, type, stepSize, in1, in2, in3, in4);
		i->f->enablePinsStepper(deviceNum, enable1, enable2);

	}

	void Stepper::steps(uint16_t _steps) {
		int32_t steps = _steps;
		if (direction) steps = -1 * steps;
		status = 1;
		//setPins();

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