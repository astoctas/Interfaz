#include "arduino.h"
#include <windows.h>
#include <WinUser.h>
#include <iostream>

using namespace std;

namespace interfaz {

	Arduino::Arduino(char* port) {
		if (f != NULL) {
			MessageBox(0, "Firmata Exists", "Interfaz", MB_OK);
			return;
		}

		try {
			/*
			serial::Serial m_serial(port, 57600);
			if(!m_serial.isOpen())	m_serial.open();
			m_serial.flush();
			m_serial.setDTR();
			m_serial.close();
			Sleep(4000); // 4 segs para reporte de version
			*/

			serialio = new firmata::FirmSerial(port);
			f = new firmata::Firmata<firmata::Base, firmata::I2C, firmata::AccelStepper, firmata::DC, firmata::LCD, firmata::Servo>(serialio);
			
		}
		catch (firmata::IOException e) {
			MessageBox(0, e.what(), "IO Exception", MB_OK);
		}
		catch (firmata::NotOpenException e) {
			MessageBox(0, e.what(), "NotOpen Exception", MB_OK);
		}
	};

	Arduino::~Arduino() {
	}

	void Arduino::parse() {
		while (true) {
			//cout << "parse" << endl;;
			try {
				if(!f->pauseParse)
					if(serialio->isOpen() && serialio->available())
						f->parse();
			}
			catch (exception e) {
				cout << e.what() << endl;
			}
		}
	}


}