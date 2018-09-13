#ifndef		__I2CPLUGIN_H_
#define		__I2CPLUGIN_H_

#include <windows.h>
#include "interfaz.h"

namespace interfaz {

	class Interfaz;

	#pragma once
	class I2Cplugin
	{
	public:
		I2Cplugin(interfaz::Interfaz* i);
		~I2Cplugin();

		virtual void command(std::string cmd, const uint8_t* data = {}) {};
		virtual void report(std::string cmd = "");
		virtual int read(uint8_t* buffer);
		virtual int readCommand(std::string cmd, uint8_t* buffer);
		virtual void writeStr(const char* str) {};
	
		void write(const uint8_t* data, uint16_t bytes);
		uint8_t readI2C8(uint8_t reg);
		uint16_t readI2C16(uint8_t reg);

		void destroy();
		void setAddress(int value);
		void setInterfaz(interfaz::Interfaz* i);
		int address = 0;
		interfaz::Interfaz* ifaz;
	protected:
		int registerToRead = 0;
		void writeI2C(std::vector<uint8_t> data);
		std::vector<uint8_t> readI2C(uint8_t reg);
		std::vector<uint8_t> readI2COnce(uint8_t reg, uint16_t bytes);
		void reportI2C(uint8_t reg, uint16_t bytes);

	};

}

#endif