#ifndef		__INTERFAZ_H_
#define		__INTERFAZ_H_

#include "arduino.h"


namespace interfaz {

	class Interfaz : public Arduino
	{
	public:
		Interfaz(char* port);
		~Interfaz();
		 
	private:
	};
}

#endif