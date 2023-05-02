#pragma once

#include <string>
#include <vector>
#define PI 3.14159
#define NEDOVOLJEN_KOT PI / 4.0

namespace igra {
	typedef std::vector<std::string> MAPA;

	struct RAZDALJA {
		double x;
		double y;
		double razdalja;
		bool zid;
		char zastavica;
		double xZ = -1;
		double yZ = -1;
		double rdZ = -1;
	};

	typedef std::vector<RAZDALJA> RAZDALJE;

	struct KOORDINATA {
		double x;
		double y;
	};

	class RC {
	private:
		RAZDALJE zarki;
		void initMapa();
		bool initM = false;
		std::vector<KOORDINATA> legalne_vrednosti;
	public:
		int mapa_x = 0;
		int mapa_y = 0;
		MAPA* mapa;
		char zid = '#';
		std::vector<char> objekti;
		double DprviKot, DzadniKot;
		bool debug = true;
		double pX = 2.0, pY = 2.0;
		double smerPogleda = PI / 2.0f;
		//double rotacija = 1.0;
		int steviloZarkov = 300;
		double FOV = PI / 8.0;
		double RD = 7.0;
		void dodajMapo(MAPA* mp);
		void operator << (MAPA* mp);
		char prnt(double x, double y);
		bool legalna(KOORDINATA k);
		void izracunajRazdalje(RAZDALJE& rd);
		void premikNaprej(double hitrost);
		void premikNazaj(double hitrost);
		void premikLevo(double hitrost);
		void premikDesno(double hitrost);
		KOORDINATA vstreli();
		KOORDINATA prikaziSmer(double razdaljaDoZida = 2, double kot = 0);
	};
}
