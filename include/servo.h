#ifndef		__SERVO_H_
#define		__SERVO_H_

#include <windows.h>
#include "stdint.h"
#include "interfaz.h"

#pragma once
using namespace interfaz;


namespace interfaz {

	class Interfaz;

	class Servo {
	public:
		Servo(interfaz::Interfaz * _i, uint8_t _deviceNum);
		~Servo();

		void setPosition(uint8_t pos);
	private:
		interfaz::Interfaz* i;
		uint8_t deviceNum;
	};

}

#endif