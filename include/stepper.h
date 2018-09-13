#ifndef		__STEPPER_H_
#define		__STEPPER_H_

#include <windows.h>
#include "stdint.h"
#include "interfaz.h"

#define MODE_STEPPER 0x08

#define STEPPER_TYPE_DRIVER		1
#define STEPPER_TYPE_TWO_WIRE	2
#define STEPPER_TYPE_THREE_WIRE 3
#define STEPPER_TYPE_FOUR_WIRE  4

#define STEPPER_STEP_SIZE_WHOLE 1
#define STEPPER_STEP_SIZE_HALF  0

#pragma once
using namespace interfaz;


namespace interfaz {

	class Interfaz;

	class Stepper {
	public:
		Stepper(interfaz::Interfaz * _i, uint8_t _deviceNum, uint8_t _step, uint8_t _dir, uint8_t _enable, uint8_t _invert);
		~Stepper();

		uint8_t direction = 0;
		double speed = 100;
		uint8_t deviceNum = 0;
		uint8_t type = STEPPER_TYPE_DRIVER;
		uint8_t stepSize = STEPPER_STEP_SIZE_WHOLE;
		void config(uint8_t _deviceNum, uint8_t _type, uint8_t _stepSize, uint8_t _stepOrMotor1Pin, uint8_t _dirOrMotor2Pin, uint8_t _enablePin, uint8_t _invertPins);
		void setConfig();
		void finishCallback();
		void steps(uint16_t _steps);
		void invert();
		void setDirection(uint8_t dir);
		void setSpeed(double _speed);
		void stop();

		uint8_t status;
		uint8_t enable, step, dir, invertPins;
	private:
		interfaz::Interfaz* i;
		uint8_t on = 0;



	};

}

#endif
