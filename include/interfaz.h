#ifndef		__INTERFAZ_H_
#define		__INTERFAZ_H_

#include "arduino.h"
#include <map>
#include <string>

#include "I2CPlugin.h"
#include "dc.h"
#include "stepper.h"
#include "servo.h"

using namespace std;

class I2Cplugin;

namespace interfaz {

	class DC;
	class Stepper;
	class Servo;

	class Interfaz : public Arduino
	{
	public:
		Interfaz(char* port);
		~Interfaz();

		//std::map<uint8_t, I2Cplugin*> I2Cplugins;
		std::vector<I2Cplugin*> I2Cplugins;

		void applyConfig();
		void setConfig(const char* model);
		void setPin(uint8_t pin, uint8_t mode);

		void setOutputs(uint8_t* _outputs);
		void outputOn();
		void outputOff();

		uint8_t I2CLoad(const char* libname);
		void I2CCommand(uint8_t index, const char* cmd, uint8_t* data);
		void I2CwriteStr(uint8_t index, const char* str);

	private:
		uint8_t led = 13;
		std::vector<uint8_t> outputs, steppers, inputs;
		std::vector<interfaz::DC*> _dc;
		std::vector<interfaz::Stepper*> _steppers;
		std::vector<interfaz::Servo*> _servos;


		struct output {
			uint8_t enable, in1, in2;
	};
		struct stepper {
			uint8_t step, dir;
			uint8_t enable;
			uint8_t invert;
		};


	struct _config {
		std::vector<output> outputs;
		std::vector<stepper> steppers;
		std::vector<uint8_t> servos;
		std::vector<uint8_t> inputs;
	} config;

	

	};
}

#endif