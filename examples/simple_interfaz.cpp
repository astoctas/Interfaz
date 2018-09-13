#include <iostream>
#pragma once
#include <windows.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iostream>
using namespace std;

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


typedef void (__stdcall *OPEN)(LPSTR);
typedef LPSTR (__stdcall *ENUM)();
typedef void (__stdcall *DW)(WORD, WORD);
typedef void (__stdcall *AW)(WORD, DWORD);
typedef void (__stdcall *RA)(WORD, WORD);
typedef void (__stdcall *PM)(WORD, WORD);
typedef DWORD (__stdcall *AR)(LPSTR);
typedef WORD(__stdcall *I2CRO)(WORD, WORD, DWORD, PBYTE);
typedef WORD(__stdcall *I2CR)( WORD, WORD, PBYTE);
typedef void(__stdcall *I2CRP)(WORD, WORD, DWORD);
typedef void (__stdcall *I2CW)(WORD, PCSTR);
typedef void (__stdcall *I2CPUSH)(WORD);
typedef WORD (__stdcall *I2CPOP)();
typedef void (__stdcall *I2CL)(PCSTR);
typedef void (__stdcall *I2CC)(uint8_t, PCSTR, PCSTR);
typedef void (__stdcall *I2CWS)(uint8_t, PCSTR);


int main(int argc, const char* argv[])
{
	HINSTANCE hinstLib;
	hinstLib = LoadLibrary("InterfazDll.dll");
	OPEN ProcAdd = (OPEN)GetProcAddress(hinstLib, "open");
	ENUM ProcEnum = (ENUM)GetProcAddress(hinstLib, "enumeratePorts");
	DW digitalWrite = (DW)GetProcAddress(hinstLib, "digitalWrite");
	RA reportAnalog = (DW)GetProcAddress(hinstLib, "reportAnalog");
	AR analogRead = (AR)GetProcAddress(hinstLib, "analogRead");
	AW analogWrite= (AW)GetProcAddress(hinstLib, "analogWrite");
	PM pinMode = (PM)GetProcAddress(hinstLib, "pinMode");
	I2CRP reportI2C = (I2CRP)GetProcAddress(hinstLib, "reportI2C");
	I2CRO readI2COnce = (I2CRO)GetProcAddress(hinstLib, "readI2COnce");
	I2CR readI2C = (I2CR)GetProcAddress(hinstLib, "readI2C");
	I2CW writeI2C = (I2CW)GetProcAddress(hinstLib, "writeI2C");
	I2CPUSH pushI2C = (I2CPUSH)GetProcAddress(hinstLib, "pushI2C");
	I2CPOP popI2C = (I2CPOP)GetProcAddress(hinstLib, "popI2C");
	I2CL I2CLoad = (I2CL)GetProcAddress(hinstLib, "I2CLoad");
	I2CC I2CCommand = (I2CC)GetProcAddress(hinstLib, "I2CCommand");
	I2CWS I2CwriteStr = (I2CWS)GetProcAddress(hinstLib, "I2CwriteStr");
	//cout << (ProcEnum)();
	char port[5] = "COM6";
	BYTE b[6] = {};
	(ProcAdd)(port);
	/*
	(reportAnalog)(1, 1);
	(reportAnalog)(2, 1);
	(reportAnalog)(3, 1);
	(reportAnalog)(4, 1);
	(reportAnalog)(5, 1);
	(reportAnalog)(6, 1);
	*/
	//(pushI2C)(HMC5883L_RA_MODE);
	//(pushI2C)(HMC5883L_MODE_CONTINUOUS << (HMC5883L_MODEREG_BIT - HMC5883L_MODEREG_LENGTH + 1));

	/*
	char * d = static_cast<char*>(GlobalAlloc(GPTR, 4));
	//char * d = {}; // static_cast<char*>(GlobalAlloc(GPTR, 4));
	sprintf_s(d, 4, "%u %u", HMC5883L_RA_MODE, HMC5883L_MODE_CONTINUOUS << (HMC5883L_MODEREG_BIT - HMC5883L_MODEREG_LENGTH + 1));
	(writeI2C)(0x1E,d);

	(pinMode)(45, 4);
	(analogWrite)(45, 100);
	(I2CLoad)("LCD");
	(I2CCommand)(0, "backlight", "");
	(I2CCommand)(0, "blink_off", "");
	(I2CCommand)(0, "cursor_off", "");
	(I2CCommand)(0, "setCursor", "5 0");
	(I2CwriteStr)(0, "Interfaz!");
	 */
	//(I2CConfig)(0x1E, "setModeContinous", "");
	/*
	l->backlight();
	l->blink_off();
	l->cursor_off();
	l->setCursor(15, 0);
	l->print("Interfaz");
	l->setCursor(15, 1);
	l->print("Neotec");
	for (int j = 0; j < 20; j++) {
		l->scrollDisplayLeft();
		Sleep(100);

	}
	*/

	//(reportI2C)(0x1E, 0x03, 6);

	while (true) {
		/*
		(digitalWrite)(13, 1);
		Sleep(500);
		(digitalWrite)(13, 0);
		Sleep(500);
		Sleep(100);
		DWORD a = (analogRead)("A1");
		cout << a << endl;
		*/
		//(pushI2C)(HMC5883L_RA_MODE);
		//(pushI2C)(HMC5883L_MODE_CONTINUOUS << (HMC5883L_MODEREG_BIT - HMC5883L_MODEREG_LENGTH + 1));
		//(writeI2C)(0x1E);
		//WORD lstr = (readI2COnce)(0x1E, 0x03, 6, b);
		//(writeI2C)(0x1E, static_cast<PCSTR>(d));
		//(analogWrite)(45, rand() % 200);
		/*
		WORD lstr = (readI2C)(0x1E, 0x03, b);
		wcout << lstr << ": ";
		for (int i = 0; i < lstr; i++) {
			//WORD lstr = (popI2C)();
			wcout << b[i] << ',';
		}
		wcout << endl;
		*/
		_sleep(500);
	}
}
