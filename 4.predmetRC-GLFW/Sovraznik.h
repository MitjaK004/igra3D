#pragma once
#include "oblike.h"
#include "okno.h"
#include <string>
#include "okno.h"
#include "RC.h"

using std::string;

namespace igra {
	struct ObmocjeRazdalj {
		int x1;
		int x2;
	};

	struct Respawn {
		float cas;
		float x;
		float y;
	};

	enum Smer {
		X = 'X', Y = 'Y', STOP = 'STOP'
	};

	struct Premik {
		float vrednost = 0.003f;
		Smer smer = X;
		bool premikam_se = false;
		float smerniKoeficient = 1;
	};

	class Sovraznik
	{
	private:
		void popraviRazdaljo(RAZDALJA& a);
		void najdiSovraznika();
		OBLIKA sovraznik_obl;
		KvadratRCT sovraznik_kvd;
		string tekstura = "sovr.png";
		OKNO* okno = nullptr;
		RAZDALJE* rd = nullptr;
		RC* rc = nullptr;
		std::vector<ObmocjeRazdalj> sovrazniki;
		STOPARCA respwn;
		Premik premik;
		float x = 2.0f, y = 2.0f;
		int resolucija = 300;
		int xint = 2, yint = 2;
		int jaz = -1;
		char popravi = '#';
		char sovraznikZastavica = '$';
		bool mrtev = false;
		void premakni();
		KLIC initTeksturaLambda = [&] {
			this->setTekstura(tekstura);
		};
	public:
		KLIC umri = [] { return; };
		Respawn respawn = { 10000, 2, 2 };
		char znakZaZid = '#';
		Sovraznik();
		Sovraznik(KOORDINATA k);
		Sovraznik(OKNO* okn, RAZDALJE* r, RC* a, KOORDINATA k = { 2, 2 }, string txttra = "sovr.png");
		KLIC dobiLambdo();
		void nastaviPotrebneVrednosti(OKNO* okn, RAZDALJE* r, RC* a, KOORDINATA k = { 2, 2 }, string txttra = "sovr.png");
		float sirina = 0.5f;
		float zdravje = 100.0f;
		float zdrav = 100.0f;
		void setTekstura(string a);
		OBLIKA& vrniObliko();
		void operator = (KOORDINATA k);
		operator KOORDINATA ();
		void nastaviPremik(Premik pr);
		void strel(KOORDINATA krd);
		void nastaviResolucijo(int a);
		void dodajOkno(OKNO* okn);
		void dodajRazdalje(RAZDALJE* r);
		void dodajRC(RC* a);
		void narisiSeNaMapo();
		void zbrisiSeIzMape();
		void noRespawn();
		void setRespawn(Respawn rp);
		void naredi();
	};
}

