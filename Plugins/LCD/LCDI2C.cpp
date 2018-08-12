// $nombredeproyecto$.cpp: define las funciones exportadas de la aplicación DLL.
//

#include "stdafx.h"
#include "inttypes.h"
#include "I2Cplugin.h"
#include "LiquidCrystal_I2C.h"

#include <iostream>
#include <vector>

using namespace std;

#define DllExport __declspec( dllexport )

#define LCD_ADDRESS 0x27

#pragma once
class LCDI2C : virtual public I2Cplugin, virtual public LiquidCrystal_I2C
{
public:
	LCDI2C(interfaz::Interfaz* i, uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) : I2Cplugin(i), LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows) 
	{
		setAddress(LCD_ADDRESS);
		registerToRead = 0;
	};
	~LCDI2C() {};

	virtual void expanderWrite(uint8_t);

	
private:

};

extern "C" DllExport I2Cplugin* __stdcall init(interfaz::Interfaz* i) {
	LCDI2C* l = new LCDI2C(i, LCD_ADDRESS, 16, 2);
	l->init();
	l->backlight();
	l->blink_off();
	l->cursor_off();
	l->setCursor(15,0);
	l->print("Interfaz");
	l->setCursor(15, 1);
	l->print("Neotec");
	for (int j = 0; j < 20; j++) {
		l->scrollDisplayLeft();
		Sleep(100);

	}

	/*
	*/
	return l;
}

void LCDI2C::expanderWrite(uint8_t _data) {
	std::vector<uint8_t> d;
	d.push_back((uint8_t)_data | _backlightval);
	writeI2C(d);
}

