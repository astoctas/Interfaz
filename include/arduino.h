#ifndef		__ARDUINO_H_
#define		__ARDUINO_H_

#include <thread>

#include "firmata.h"
#include "firmio.h"
#include "firmbase.h"
#include "firmi2c.h"
#include "firmaccelstepper.h"
#include "firmdc.h"
#include "firmlcd.h"
#include "firmservo.h"
#include "firmserial.h"


namespace interfaz {

	class Arduino
	{
	public:
		Arduino(char* port);
		~Arduino();

		firmata::Firmata<firmata::Base, firmata::I2C, firmata::AccelStepper, firmata::DC, firmata::LCD, firmata::Servo>* f = NULL;
		firmata::FirmSerial* serialio;

		void parse();
	private:

	};
}

#endif