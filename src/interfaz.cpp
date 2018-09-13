#include "interfaz.h"
#include <windows.h>
#include <WinUser.h>
#include <iostream>
#include <iterator>


namespace interfaz {

	Interfaz::Interfaz(char* port) : Arduino(port) {
		setConfig("MEGA");
		applyConfig();
		cout << "encender" << endl;
		uint8_t s[] = {1};
		/*
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
		
		*/ 
		_steppers.at(0)->setSpeed(100);

		_steppers.at(0)->invert();
		_steppers.at(0)->steps(1000);
		Sleep(2000);
		//_steppers.at(0)->stop();
		//f->writeI2C(0x27, { 0x00, 0x02});
		//f->writeI2C(0x27, { 0x01, 65});
		



	};

	Interfaz::~Interfaz() {
	}


	void Interfaz::setPin(uint8_t pin, uint8_t mode) {
		if (f->getPin(pin).mode != mode) f->pinMode(pin, mode);
	}


	void Interfaz::setConfig(const char* model) {
		if (string(model) == "MEGA") {
			config.outputs.push_back({ 4,22,23 });
			config.outputs.push_back({ 5,24,25 });
			config.outputs.push_back({ 6,26,27 });
			config.outputs.push_back({ 7,28,29 });
			config.outputs.push_back({ 8,30,31 });
			config.outputs.push_back({ 9,32,33 });
			config.outputs.push_back({ 10,34,35 });
			config.outputs.push_back({ 11,36,37 });
			config.steppers.push_back({ 38,39,40,0b00010000 });
			config.steppers.push_back({ 41,42,43,0b00010000 });
			config.steppers.push_back({ 47,48,49,0b00010000 });
			config.servos.insert(config.servos.end(), { 44,45,46 });
			config.inputs.insert(config.inputs.end(),{ 54,55,56,57,58,59,60,61 });
		}
	}


	void Interfaz::applyConfig() {
		for (int j = 0; j < config.outputs.size() - 1; j++) {
			_dc.push_back(new interfaz::DC(this, j, config.outputs.at(j).enable, config.outputs.at(j).in1, config.outputs.at(j).in2));
		}
		for (int j = 0; j < config.steppers.size() - 1; j++) {
			_steppers.push_back(new interfaz::Stepper(this, j, config.steppers.at(j).step, config.steppers.at(j).dir, config.steppers.at(j).enable, config.steppers.at(j).invert));
		}

		for (int j = 0; j < config.servos.size() - 1; j++) {
			_servos.push_back(new interfaz::Servo(this, config.servos.at(j)));
		}


	}

	void Interfaz::setOutputs(uint8_t* _outputs) {
		std:vector<uint8_t> o(_outputs, _outputs + sizeof _outputs / sizeof uint8_t);
		outputs.assign(o.begin(), o.end());
	}


	void Interfaz::outputOn() {
		for (vector<uint8_t>::iterator it = outputs.begin(); it != outputs.end(); it++) {
			if(*it - 1 < _dc.size())
				_dc.at(*it - 1)->turnOn();
		}
	}

	void Interfaz::outputOff() {
		for (vector<uint8_t>::iterator it = outputs.begin(); it != outputs.end(); it++) {
			if (*it - 1 < _dc.size())
				_dc.at(*it - 1)->turnOff();
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


}



