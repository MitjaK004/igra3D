#pragma once
#include "oblike.h"
#include "cas.h"
#include "animacija.h"
#include <functional>

namespace igra {

	class Orozje
	{
		OBLIKA orozje;
		ANIMACIJA _reloadaj;
		ANIMACIJA _vstreli;
	public:
		Orozje();
		Orozje(std::string a);
		void operator = (std::string a);
		void reloadaj(STOPARCA& st);
		void vstreli(STOPARCA& st);
		void setReloadAnimacijo(ANIMACIJA a);
		void setStreljanjeAnimacijo(ANIMACIJA a);
		OBLIKA* dobiObliko();
	};
}

