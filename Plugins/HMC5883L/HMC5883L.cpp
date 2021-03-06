// $nombredeproyecto$.cpp: define las funciones exportadas de la aplicación DLL.
//

#include "stdafx.h"
#include "I2Cplugin.h"

#include <iostream>
#include <vector>

using namespace std;

#define HMC5883L_ADDRESS              (0x1E)
#define HMC5883L_REG_CONFIG_A         (0x00)
#define HMC5883L_REG_CONFIG_B         (0x01)
#define HMC5883L_REG_MODE             (0x02)
#define HMC5883L_REG_OUT_X_M          (0x03)
#define HMC5883L_REG_OUT_X_L          (0x04)
#define HMC5883L_REG_OUT_Z_M          (0x05)
#define HMC5883L_REG_OUT_Z_L          (0x06)
#define HMC5883L_REG_OUT_Y_M          (0x07)
#define HMC5883L_REG_OUT_Y_L          (0x08)
#define HMC5883L_REG_STATUS           (0x09)
#define HMC5883L_REG_IDENT_A          (0x0A)
#define HMC5883L_REG_IDENT_B          (0x0B)
#define HMC5883L_REG_IDENT_C          (0x0C)

typedef enum
{
	HMC5883L_SAMPLES_8 = 0b11,
	HMC5883L_SAMPLES_4 = 0b10,
	HMC5883L_SAMPLES_2 = 0b01,
	HMC5883L_SAMPLES_1 = 0b00
} hmc5883l_samples_t;

typedef enum
{
	HMC5883L_DATARATE_75HZ = 0b110,
	HMC5883L_DATARATE_30HZ = 0b101,
	HMC5883L_DATARATE_15HZ = 0b100,
	HMC5883L_DATARATE_7_5HZ = 0b011,
	HMC5883L_DATARATE_3HZ = 0b010,
	HMC5883L_DATARATE_1_5HZ = 0b001,
	HMC5883L_DATARATE_0_75_HZ = 0b000
} hmc5883l_dataRate_t;

typedef enum
{
	HMC5883L_RANGE_8_1GA = 0b111,
	HMC5883L_RANGE_5_6GA = 0b110,
	HMC5883L_RANGE_4_7GA = 0b101,
	HMC5883L_RANGE_4GA = 0b100,
	HMC5883L_RANGE_2_5GA = 0b011,
	HMC5883L_RANGE_1_9GA = 0b010,
	HMC5883L_RANGE_1_3GA = 0b001,
	HMC5883L_RANGE_0_88GA = 0b000
} hmc5883l_range_t;

typedef enum
{
	HMC5883L_IDLE = 0b10,
	HMC5883L_SINGLE = 0b01,
	HMC5883L_CONTINOUS = 0b00
} hmc5883l_mode_t;

#define DllExport __declspec( dllexport )

#pragma once
class HMC5883L: public interfaz::I2Cplugin
{
public:
	HMC5883L(interfaz::Interfaz* i) : I2Cplugin(i) {
		setAddress(HMC5883L_ADDRESS);
		registerToRead = HMC5883L_REG_OUT_X_M;
	};
	~HMC5883L() {};

	virtual void command(std::string cmd, const uint8_t* data = {});
	virtual void report(std::string cmd = "");
	virtual int readCommand(std::string cmd, uint8_t* buffer);

private:
	void setMeasurementMode(uint8_t mode);

};

extern "C" DllExport interfaz::I2Cplugin* __stdcall init(interfaz::Interfaz* i) {
	return new HMC5883L(i);
}



int HMC5883L::readCommand(std::string cmd, uint8_t* buffer) {
	std::vector<uint8_t> data;
	if (cmd == "XYZ" || cmd == "") 
		data = readI2COnce(HMC5883L_REG_OUT_X_M, 6);
	if (cmd == "X")
		data = readI2COnce(HMC5883L_REG_OUT_X_M, 2);
	if (cmd == "Y")
		data = readI2COnce(HMC5883L_REG_OUT_Y_M, 2);
	if (cmd == "Z")
		data = readI2COnce(HMC5883L_REG_OUT_Z_M, 2);
	memcpy(buffer, data.data(), data.size());
	return data.size();

}


void HMC5883L::report(std::string cmd) {
	if (cmd == "XYZ" || cmd == "") {
		registerToRead = HMC5883L_REG_OUT_X_M;
		reportI2C(registerToRead, 6);
		return;
	}
	if (cmd == "X")
		registerToRead = HMC5883L_REG_OUT_X_M;
	if (cmd == "Y") 
		registerToRead = HMC5883L_REG_OUT_Y_M;
	if (cmd == "Z") 
		registerToRead = HMC5883L_REG_OUT_Z_M;
	reportI2C(registerToRead, 2);
}

void HMC5883L::command(std::string cmd, const uint8_t* data) {
	if (cmd == "setModeContinous") {
		setMeasurementMode(HMC5883L_CONTINOUS);
	}
	if (cmd == "setModeSingle") {
		setMeasurementMode(HMC5883L_SINGLE);
	}
	if (cmd == "setMeasurementMode") {
			setMeasurementMode(data[0]);
	} 
}

void HMC5883L::setMeasurementMode(uint8_t mode) {
	cout << "MODE" << endl;
	uint8_t value = readI2C8(HMC5883L_REG_MODE);
	value &= 0b11111100;
	value |= mode;
	writeI2C({ HMC5883L_REG_MODE , value });
}

