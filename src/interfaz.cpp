#include "interfaz.h"
#include <windows.h>
#include <WinUser.h>
#include <iostream>
#include <iterator>


namespace interfaz {

	Interfaz::Interfaz(char* _port, uint8_t _deviceNum) : Arduino(_port) {
		port = _port;
		deviceNum = _deviceNum;

		f->clearLCD();
		string a("Conectado: ");
		string p(port);
		a.append(p);
		f->pushLCD(a.c_str());
		string b("Soy interfaz: ");
		b.append(std::to_string(deviceNum + 1));
		f->pushLCD(b.c_str());


		setConfig("MEGA");
		applyConfig();
		/*
		cout << "encender" << endl;
		std::vector<uint8_t> s;
		s.push_back(1);
		setOutputs(s);
		outputOn();
		_dc.at(0)->turnOn();
		Sleep(1000);
		_dc.at(0)->brake();
		Sleep(1000);
		_dc.at(0)->turnOn();
		Sleep(1000);
		_dc.at(0)->invert();
		Sleep(1000);
		_dc.at(0)->turnOff();
		_servos.at(0)->setPosition(100);
		//_steppers.at(0)->setSpeed(100);


		_steppers.at(0)->steps(-100);
		_steppers.at(0)->invert();
	//	_dc.at(0)->turnOn();
		_servos.at(0)->setPosition(50);

		Sleep(2000);
		//_steppers.at(0)->stop();
		//f->writeI2C(0x27, { 0x00, 0x02});
		//f->writeI2C(0x27, { 0x01, 65});

		*/
		//f->configI2C(200);
		/*
		std::cout << "leyendo" << endl;
		f->writeI2C(0x40, {0xFE});
		std::vector<uint8_t> data = f->readI2COnce(0x40, 0xe7, 1);
		std::cout << std::to_string(data.size()) << endl;
		for (auto i = data.begin(); i != data.end(); ++i)
			std::cout << *i << ' ';

		std::vector<uint8_t>  data = f->readI2COnce(0x40, 0xe3, 3);
		std::cout << std::to_string(data.size()) << endl;
		for (auto i = data.begin(); i != data.end(); ++i)
			std::cout << *i << ' ';
		std::cout << "fin leyendo" << endl;
		*/


	};

	Interfaz::~Interfaz() {
	}


	void Interfaz::setPin(uint8_t pin, uint8_t mode) {
		if (f->getPin(pin).mode != mode) f->pinMode(pin, mode);
	}


	void Interfaz::setConfig(const char* model) {
		if (string(model) == "MEGA") {
			config.max_dc = 8;
			config.max_steppers = 3;
			config.servos.insert(config.servos.end(), { 10,11,12 });
			config.inputs.insert(config.inputs.end(),{ 54,55,56,57,58,59,60,61 });
		}
	}


	void Interfaz::applyConfig() {
		for (int j = 0; j < config.max_dc; j++) {
			_dc.push_back(new interfaz::DC(this, j));
		}
		for (int j = 0; j < config.max_steppers; j++) {
			_steppers.push_back(new interfaz::Stepper(this, j));
			//_steppers.at(j)->setSpeed(_steppers.at(j)->speed);
		}

		for (int j = 0; j < config.servos.size(); j++) {
			_servos.push_back(new interfaz::Servo(this, config.servos.at(j)));
		}


	}

	void Interfaz::setOutputs(std::vector<uint8_t> _outputs) {
		outputs.assign(_outputs.begin(), _outputs.end());
	}
	
	void Interfaz::setSteppers(std::vector<uint8_t> _outputs) {
		steppers.assign(_outputs.begin(), _outputs.end());
	}

	void Interfaz::setServos(std::vector<uint8_t> _outputs) {
		servos.assign(_outputs.begin(), _outputs.end());
	}


	void Interfaz::outputsOn() {
		for (vector<uint8_t>::iterator it = outputs.begin(); it != outputs.end(); it++) {
			if(*it - 1 < _dc.size())
				_dc.at(*it - 1)->turnOn();
		}
	}

	void Interfaz::outputsOff() {
		for (vector<uint8_t>::iterator it = outputs.begin(); it != outputs.end(); it++) {
			if (*it - 1 < _dc.size())
				_dc.at(*it - 1)->turnOff();
		}
	}

	void Interfaz::outputsDir(uint8_t dir) {
		for (vector<uint8_t>::iterator it = outputs.begin(); it != outputs.end(); it++) {
			if (*it - 1 < _dc.size())
				_dc.at(*it - 1)->setDirection(dir);
		}
	}
	
	void Interfaz::outputsSpeed(uint8_t speed) {
		for (vector<uint8_t>::iterator it = outputs.begin(); it != outputs.end(); it++) {
			if (*it - 1 < _dc.size())
				_dc.at(*it - 1)->setSpeed(speed);
		}
	}
	
	void Interfaz::outputsBrake() {
		for (vector<uint8_t>::iterator it = outputs.begin(); it != outputs.end(); it++) {
			if (*it - 1 < _dc.size())
				_dc.at(*it - 1)->brake();
		}
	}
	
	void Interfaz::outputsReverse() {
		for (vector<uint8_t>::iterator it = outputs.begin(); it != outputs.end(); it++) {
			if (*it - 1 < _dc.size())
				_dc.at(*it - 1)->inverse();
		}
	}

	void Interfaz::steppersSteps(uint16_t _steps) {
		for (vector<uint8_t>::iterator it = steppers.begin(); it != steppers.end(); it++) {
			if (*it - 1 < _steppers.size())
				_steppers.at(*it - 1)->steps(_steps);
		}
	}

	void Interfaz::steppersStop() {
		for (vector<uint8_t>::iterator it = steppers.begin(); it != steppers.end(); it++) {
			if (*it - 1 < _steppers.size())
				_steppers.at(*it - 1)->stop();
		}
	}

	void Interfaz::steppersDir(uint8_t dir) {
		for (vector<uint8_t>::iterator it = steppers.begin(); it != steppers.end(); it++) {
			if (*it - 1 < _steppers.size())
				_steppers.at(*it - 1)->setDirection(dir);
		}
	}

	void Interfaz::servosPosition(uint8_t pos) {
		for (vector<uint8_t>::iterator it = servos.begin(); it != servos.end(); it++) {
			if (*it - 1 < _servos.size())
				_servos.at(*it - 1)->setPosition(pos);
		}
	}

	void Interfaz::setAnalog(uint8_t channel, uint8_t enable) {
		inputs.clear();
		if(enable) inputs.push_back(channel);
		f->reportAnalog(channel - 1, enable);
	}

	uint16_t Interfaz::analogValue() {
		if (inputs.size()) {
			string a("A");
			string p(std::to_string(inputs.at(0) - 1));
			a.append(p);
			return f->analogRead(a);
		}
		return -1;
	}

	void Interfaz::setI2C(uint8_t address, uint32_t delay) {
		i2c.clear();
		i2c.push_back(address);
		f->configI2C(delay);
	}

	void Interfaz::i2cReport(uint16_t _register, uint32_t bytes) {
		if (i2c.size()) {
			f->reportI2C(i2c.at(0), _register, bytes);
		}
	}

	std::vector<uint8_t> Interfaz::i2cRead(uint16_t _register, uint32_t bytes) {
		if (i2c.size()) {
			return f->readI2COnce(i2c.at(0), _register, bytes);
		}
		return {};
	}

	std::vector<uint8_t> Interfaz::i2cValue(uint16_t _register) {
		if (i2c.size()) {
			return f->readI2C(i2c.at(0), _register);
		}
		return {};
	}

	void Interfaz::i2cWrite(std::vector<uint8_t> data) {
		if (i2c.size()) {
			return f->writeI2C(i2c.at(0), data);
		}
	}


	uint8_t Interfaz::I2CLoad(const char* libname) {

		string lib(libname);
		typedef I2Cplugin* (__stdcall *INIT)(interfaz::Interfaz*);
		HINSTANCE hinstLib = ::LoadLibrary(string(lib + ".dll").c_str());
		INIT InitProc = reinterpret_cast<INIT>(::GetProcAddress(hinstLib, "_init@4"));
		I2Cplugin* p = (InitProc)(this);
		I2Cplugins.push_back(p);
		return I2Cplugins.size() - 1;
	}

	void Interfaz::I2CCommand(uint8_t index, const char* cmd, uint8_t* data) {
		I2Cplugin* p = static_cast<I2Cplugin*>(I2Cplugins.at(index));
		p->command(cmd, data);
	}

	void Interfaz::I2CwriteStr(uint8_t index, const char* str) {
		I2Cplugin* p = static_cast<I2Cplugin*>(I2Cplugins.at(index));
		p->writeStr(str);
	}

	void Interfaz::close() {
		serialio->close();
	}

}



