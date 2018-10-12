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
		Interfaz(char* _port, uint8_t _deviceNum);
		~Interfaz();

		//std::map<uint8_t, I2Cplugin*> I2Cplugins;
		std::vector<I2Cplugin*> I2Cplugins;

		void applyConfig();
		void setConfig(const char* model);
		void setPin(uint8_t pin, uint8_t mode);

		void setOutputs(std::vector<uint8_t> _outputs);
		void setSteppers(std::vector<uint8_t> _outputs);
		void setServos(std::vector<uint8_t> _outputs);
		void outputsOn();
		void outputsOff();
		void outputsDir(uint8_t dir);
		void outputsSpeed(uint8_t speed);
		void outputsBrake();
		void outputsReverse();
		
		void steppersSteps(uint16_t _steps);
		void steppersStop();
		void steppersDir(uint8_t dir);
		
		void servosPosition(uint8_t pos);

		void setAnalog(uint8_t channel, uint8_t enable);
		uint16_t analogValue();

		void setI2C(uint8_t address, uint32_t delay = 100);
		void i2cReport(uint16_t _register, uint32_t bytes);
		std::vector<uint8_t> i2cRead(uint16_t _register, uint32_t bytes);
		std::vector<uint8_t> i2cValue();
		void i2cWrite(std::vector<uint8_t> data);



		uint8_t I2CLoad(const char* libname);
		void I2CCommand(uint8_t index, const char* cmd, uint8_t* data);
		void I2CwriteStr(uint8_t index, const char* str);

		void close();

	private:
		uint8_t led = 13;
		std::vector<uint8_t> outputs, steppers, servos, inputs, i2c;
		uint16_t i2cRegister;
		std::vector<interfaz::DC*> _dc;
		std::vector<interfaz::Stepper*> _steppers;
		std::vector<interfaz::Servo*> _servos;
		uint8_t deviceNum;
		char* port;


		struct output {
			uint8_t enable, in1, in2;
	};
		struct stepper {
			uint8_t step, dir;
			uint8_t enable;
			uint8_t invert;
		};


	struct _config {
		int max_dc;
		int max_steppers;
		std::vector<uint8_t> servos;
		std::vector<uint8_t> inputs;
	} config;

	

	};
}

#endif