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
class LCDI2C : virtual public interfaz::I2Cplugin, virtual public LiquidCrystal_I2C
{
public:
	LCDI2C(interfaz::Interfaz* i, uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) : I2Cplugin(i), LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows) 
	{
		setAddress(LCD_ADDRESS);
		registerToRead = 0;
	};
	~LCDI2C() {};

	virtual void expanderWrite(uint8_t);
	virtual void command(std::string cmd, const uint8_t* data);
	virtual void writeStr(const char* str);
	
private:

};

extern "C" DllExport interfaz::I2Cplugin* __stdcall init(interfaz::Interfaz* i) {
	LCDI2C* l = new LCDI2C(i, LCD_ADDRESS, 16, 2);
	l->init();
	return l;
}

void LCDI2C::expanderWrite(uint8_t _data) {
	std::vector<uint8_t> d;
	d.push_back((uint8_t)_data | _backlightval);
	writeI2C(d);
}

void LCDI2C::writeStr(const char* str) {
	string s(str);
	print(s);
}

void LCDI2C::command(std::string cmd, const uint8_t* data) {
	if (cmd == "backlight") backlight(); 
	if (cmd == "blink_off") blink_off();
	if (cmd == "blink_on") blink_on();
	if (cmd == "cursor_off") cursor_off();
	if (cmd == "cursor_on") cursor_on();
	if (cmd == "scrollDisplayLeft") scrollDisplayLeft();
	if (cmd == "scrollDisplayRight") scrollDisplayRight();
	if (cmd == "setCursor") setCursor(data[0], data[1]);
}

