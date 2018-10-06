#ifndef		__DC_H_
#define		__DC_H_

#include <windows.h>
#include "stdint.h"
#include "interfaz.h"

#pragma once
using namespace interfaz;


namespace interfaz {

	class Interfaz;

	class DC {
	public:
		DC(interfaz::Interfaz * _i, uint8_t _deviceNum);
		~DC();

		uint8_t direction = 0, power = 255;

		void turnOn();
		void turnOff();
		void brake();
		void inverse();
		void setDirection(uint8_t dir);
		void setSpeed(uint8_t speed);
	private:
		interfaz::Interfaz* i;
		uint8_t deviceNum;
		uint8_t enable, in1, in2;
		uint8_t on = 0;
	};

}

#endif