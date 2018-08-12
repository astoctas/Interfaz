#include "I2Cplugin.h"

I2Cplugin::I2Cplugin(interfaz::Interfaz* i)
{
	interfaz::Interfaz* ifaz = static_cast<interfaz::Interfaz*>(GlobalAlloc(GPTR, sizeof(interfaz::Interfaz)));
	setInterfaz(i);
}


I2Cplugin::~I2Cplugin()
{
}


void I2Cplugin::destroy()
{
	delete this;
}

void I2Cplugin::setAddress(int value)
{
	address = value;
}

void I2Cplugin::setInterfaz(interfaz::Interfaz* i)
{
	ifaz = i;
}


int I2Cplugin::read(uint8_t* buffer) {
	std::vector<uint8_t> data;
	data = readI2C(registerToRead);
	memcpy(buffer, data.data(), data.size());
	return data.size();
}

void I2Cplugin::write(const uint8_t* data, uint16_t bytes) {
	try {
		std::vector<uint8_t> v(&data[0], &data[bytes - 1]);
		ifaz->f->writeI2C(address, v);
	} catch(exception e) {}
}

int I2Cplugin::readCommand(std::string cmd, uint8_t* buffer) {
	std::vector<uint8_t> data;
	if (cmd == "")
		data = readI2COnce(registerToRead, 2);
	memcpy(buffer, data.data(), data.size());
	return data.size();

}

void I2Cplugin::report(std::string cmd) {
	if (cmd == "") {
		reportI2C(registerToRead, 2);
	}
}

void I2Cplugin::writeI2C(const std::vector<uint8_t> data) {
	ifaz->f->writeI2C(address, data);
}

uint8_t I2Cplugin::readI2C8(uint8_t reg) {
	std::vector<uint8_t> data = ifaz->f->readI2COnce(address, reg, 1);
	if (data.size()) {
		return data[0];
	}
	return 0;
}


uint16_t I2Cplugin::readI2C16(uint8_t reg) {
	std::vector<uint8_t> data = ifaz->f->readI2COnce(address, reg, 2);
	if (data.size() > 1) {
		uint16_t value;
		value = data[0] << 8 | data[1];
		return value;
	}
	return 0;
}

std::vector<uint8_t> I2Cplugin::readI2C(uint8_t reg) {
	return ifaz->f->readI2C(address, reg);
}

std::vector<uint8_t> I2Cplugin::readI2COnce(uint8_t reg, uint16_t bytes) {
	return ifaz->f->readI2COnce(address, reg, bytes);
}

void I2Cplugin::reportI2C(uint8_t reg, uint16_t bytes) {
	return ifaz->f->reportI2C(address, reg, bytes);
}


