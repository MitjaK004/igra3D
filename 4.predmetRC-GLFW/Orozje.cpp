#include "Orozje.h"
#include "animacija.h"

namespace igra {
	Orozje::Orozje() {
		orozje.init();
	}
	Orozje::Orozje(std::string a) {
		orozje.Tekstura(a.c_str());
		orozje.init();
	}
	void Orozje::operator=(std::string a) {
		orozje.Tekstura(a.c_str());
		orozje.init();
	}
	void Orozje::reloadaj(STOPARCA& st) {
		_reloadaj();
	}
	void Orozje::vstreli(STOPARCA& st) {
		_vstreli();
	}
	void Orozje::setReloadAnimacijo(ANIMACIJA a){
		_reloadaj = a;
	}
	void Orozje::setStreljanjeAnimacijo(ANIMACIJA a){
		_vstreli = a;
	}
	OBLIKA* Orozje::dobiObliko(){
		return &orozje;
	}
}