#ifndef		__STEPPER_H_
#define		__STEPPER_H_

#include <windows.h>
#include "stdint.h"
#include "interfaz.h"

#define MODE_STEPPER 0x08

#define STEPPER_TYPE_DRIVER = 1
#define STEPPER_TYPE_TWO_WIRE = 2
#define STEPPER_TYPE_THREE_WIRE = 3
#define STEPPER_TYPE_FOUR_WIRE = 4

#define STEPPER_STEP_SIZE_WHOLE = 1
#define STEPPER_STEP_SIZE_HALF = 0

#pragma once
using namespace interfaz;


namespace interfaz {

	class Interfaz;

	class Stepper {
	public:
		Stepper(interfaz::Interfaz * _i, uint8_t _deviceNum, uint8_t _enable1, uint8_t _enable2, uint8_t _in1, uint8_t _in2, uint8_t _in3, uint8_t _in4);
		~Stepper();

		uint8_t direction = 0;
		double speed = 100;
		uint8_t deviceNum = 0, type = 4, stepSize = 1;
		void config(uint8_t _deviceNum, uint8_t _type, uint8_t _stepSize, uint8_t _dirOrMotor1Pin, uint8_t _dirOrMotor2Pin, uint8_t _motorPin3, uint8_t _motorPin4, uint8_t enablePin);
		void setConfig();
		void finishCallback();
		void steps(uint16_t _steps);
		void invert();
		void setDirection(uint8_t dir);
		void setSpeed(double _speed);
		void stop();

		uint8_t status;
		uint8_t enable1, enable2, in1, in2, in3, in4;
	private:
		void setPins();
		interfaz::Interfaz* i;
		uint8_t on = 0;



	};

}

#endif
