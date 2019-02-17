#include <iostream>
#include "windows.h"
#include "firmata.h"
#include "firmserial.h"
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iostream>
#ifndef WIN32
#include "unistd.h"
#endif

#define HMC5883L_RA_MODE            0x02
#define HMC5883L_RA_DATAX_H         0x03
#define HMC5883L_RA_DATAX_L         0x04
#define HMC5883L_RA_DATAZ_H         0x05
#define HMC5883L_RA_DATAZ_L         0x06
#define HMC5883L_RA_DATAY_H         0x07
#define HMC5883L_RA_DATAY_L         0x08

#define HMC5883L_MODEREG_BIT        1
#define HMC5883L_MODEREG_LENGTH     2

#define HMC5883L_MODE_CONTINUOUS    0x00
#define HMC5883L_MODE_SINGLE        0x01
#define HMC5883L_MODE_IDLE          0x02

#define HMC5883L_STATUS_LOCK_BIT    1
#define HMC5883L_STATUS_READY_BIT   0

/*
 * Detect first serial port with a StandardFirmata interface
 * Read analog inputs A0 and A1 and digital pin 2 (eg, a Playstation analog stick + button)
 * as well as I2C address 8 (eg, the slave_sender example that comes with Arduino IDE)
 * and print to stdout
 */

int main(int argc, const char* argv[])
{
	std::vector<firmata::PortInfo> ports = firmata::FirmSerial::listPorts();
	firmata::Firmata<firmata::Base, firmata::I2C>* f = NULL;
	firmata::FirmSerial* serialio;
	/*
	
	for (auto port : ports) {
		std::cout << port.port << std::endl;

		if (f != NULL) {
			delete f;
			f = NULL;
		}

		try {
			serialio = new firmata::FirmSerial(port.port.c_str());
#ifndef WIN32
			if (serialio->available()) {
				sleep(3); // Seems necessary on linux
				f = new firmata::Firmata<firmata::Base, firmata::I2C>(serialio);
			}
#else
			f = new firmata::Firmata<firmata::Base, firmata::I2C>(serialio);
#endif
		} 
		catch(firmata::IOException e) {
			std::cout << e.what() << std::endl;
		}
		catch(firmata::NotOpenException e) {
			std::cout << e.what() << std::endl;
		}
		if (f != NULL && f->ready()) {
			break;
		}
	}

	if (f == NULL || !f->ready()) {
		return 1;
	}
	*/

	serial::Serial m_serial("COM6", 57600);
	if (!m_serial.isOpen())	m_serial.open();
	m_serial.flush();
	m_serial.setDTR();
	m_serial.close();
	Sleep(4000); // 4 segs para reporte de version

	serialio = new firmata::FirmSerial("COM6");
	f = new firmata::Firmata<firmata::Base, firmata::I2C>(serialio);

	try {
		f->setSamplingInterval(100);

		std::cout << f->name << std::endl;
		std::cout << f->major_version << std::endl;
		std::cout << f->minor_version << std::endl;

		f->pinMode(2, MODE_INPUT);
		Sleep(10);
		/*
		f->reportAnalog(0, 1);
		Sleep(10);
		f->reportAnalog(1, 1);
		Sleep(10);

		f->reportDigital(0, 1);
		Sleep(10);
		//f->configI2C(0);
		Sleep(10);
		*/
		Sleep(10);

		std::vector<uint8_t> dataWrite = { HMC5883L_RA_MODE, HMC5883L_MODE_CONTINUOUS << (HMC5883L_MODEREG_BIT - HMC5883L_MODEREG_LENGTH + 1) };
		f->writeI2C(0x1E, dataWrite);
		//f->reportI2C(0x1E, HMC5883L_RA_DATAX_H, 6);


		while (true) {
			try {
				f->parse();
			/*
			int a0 = f->analogRead("A0");
			int a1 = f->analogRead("A1");
			int pin2 = f->digitalRead(2);
			*/
			//std::vector<uint8_t> data = f->readI2C(0x1E, HMC5883L_RA_DATAX_H);
			std::vector<uint8_t> data = f->readI2COnce(0x1E, HMC5883L_RA_DATAX_H,6);
			std::vector<uint8_t> dataWrite = { HMC5883L_RA_MODE, HMC5883L_MODE_CONTINUOUS << (HMC5883L_MODEREG_BIT - HMC5883L_MODEREG_LENGTH + 1) };
			f->writeI2C(0x1E, dataWrite);
			std::ostringstream oss;

			if (!data.empty())
			{
				std::copy(data.begin(), data.end() - 1,
					std::ostream_iterator<int>(oss, ","));
				// Now add the last element with no delimiter
				oss << (int)data.back();
			}
			/*
			std::string s = "";
			for (auto byte = i2c.begin(); byte < i2c.end(); ++byte) {
				s += (char)*byte;
			}
			*/
			//std::cout << "REport: " << a0 << ", " << a1 << ", " << pin2 <<  ", " << s << std::endl;
			std::cout << "Report: "  << oss.str().c_str() << std::endl;
			}
			catch (std::exception e) {
				std::cout << e.what() << std::endl;
				continue;
			}
		};

		delete f;
	}
	catch (firmata::IOException e) {
		std::cout << e.what() << std::endl;
	}
	catch (firmata::NotOpenException e) {
		std::cout << e.what() << std::endl;
	}
}
