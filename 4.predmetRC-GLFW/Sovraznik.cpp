#include "Sovraznik.h"
#include <math.h>
#include <cmath>
#include <algorithm>

namespace igra {
	OBLIKA& Sovraznik::vrniObliko() {
		sovraznik_obl.kvadratRCT(sovraznik_kvd);
		sovraznik_obl.Tekstura(tekstura.c_str());
		return sovraznik_obl;
	}
	void Sovraznik::setTekstura(string a) {
		tekstura = a;
		sovraznik_obl.Tekstura(a.c_str());
		sovraznik_obl.init();
	}
	void Sovraznik::dodajOkno(OKNO* okn) {
		okno = okn;
	}
	void Sovraznik::dodajRazdalje(RAZDALJE* r) {
		rd = r;
	}
	void Sovraznik::dodajRC(RC* a) {
		rc = a;
	}
	void Sovraznik::operator=(KOORDINATA k) {
		if (!mrtev) {
			zbrisiSeIzMape();
			x = k.x;
			y = k.y;
			xint = (int)k.x;
			yint = (int)k.y;
			narisiSeNaMapo();
		}
	}
	void Sovraznik::zbrisiSeIzMape() {
		if (rc->mapa->at(yint).at(xint) != znakZaZid && xint <= rc->mapa_x && yint <= rc->mapa_y) {
			rc->mapa->at(yint).at(xint) = ' ';
		}
	}
	Sovraznik::operator igra::KOORDINATA() {
		return { x, y };
	}
	void Sovraznik::popraviRazdaljo(RAZDALJA& a) {
		float rx = abs(rc->pX - a.xZ);
		float ry = abs(rc->pY - a.yZ);
		float razdalja = sqrtf(rx*rx + ry*ry);
		a.xZ = x;
		a.yZ = y;
		a.rdZ = razdalja;
	}
	void Sovraznik::nastaviPremik(Premik pr) {
		premik = pr;
		return;
	}
	void Sovraznik::najdiSovraznika() {
		if (sovrazniki.size() > 0) {
			sovrazniki.clear();
		}
		bool sovr = false;
		char zastavica = -1;
		int x1 = -1;

		int LX = -1;
		int LY = -1;

		for (int c = 0; c < rd->size(); c++) {
			if (!sovr && rd->at(c).zastavica == sovraznikZastavica) {
				sovr = true;
				zastavica = rd->at(c).zastavica;
				x1 = c;
				LX = (int)rd->at(c).xZ;
				LY = (int)rd->at(c).yZ;
			}
			if (sovr && zastavica != rd->at(c).zastavica && x1 != -1) {
				sovr = false;
				sovrazniki.push_back({x1, c - 1});
				zastavica = -1;
				x1 = -1;
				LX = -1;
				LY = -1;
			}
			if (sovr && LX != -1 && ( LX != (int)rd->at(c).xZ || LY != (int)rd->at(c).yZ)) {
				sovr = false;
				sovrazniki.push_back({ x1, c - 1 });
				zastavica = -1;
				x1 = -1;
				LX = -1;
				LY = -1;
			}
		}
		jaz = -1;
		for (int c = 0; c < sovrazniki.size(); c++) {
			if ((int)rd->at(sovrazniki.at(c).x1).xZ == (int)x && (int)rd->at(sovrazniki.at(c).x1).yZ == (int)y) {
				xint = (int)rd->at(sovrazniki.at(c).x1).xZ;
				yint = (int)rd->at(sovrazniki.at(c).x1).yZ;
				jaz = c;
				break;
			}
		}
	}
	void Sovraznik::premakni() {
		if (premik.smer == X && premik.premikam_se) {
			if (rc->legalna({ x + premik.vrednost * premik.smerniKoeficient, y }) != znakZaZid) {
				x += premik.vrednost * premik.smerniKoeficient;
			}
			if (!rc->legalna({ x + premik.vrednost * premik.smerniKoeficient, y }))
			{
				if(rc->legalna({ x, y + premik.vrednost * premik.smerniKoeficient })) {
					premik.smer = Y;
				}
				else {
					premik.smer = STOP;
				}
			}
		}
		if (premik.smer == Y && premik.premikam_se) {
			if (rc->legalna({ x, y + premik.vrednost * premik.smerniKoeficient })) {
				y += premik.vrednost * premik.smerniKoeficient;
			}
			if (!rc->legalna({x, y + premik.vrednost * premik.smerniKoeficient}))
			{
				if (rc->legalna({ x + premik.vrednost * premik.smerniKoeficient, y })) {
					premik.smer = X;
				}
				else {
					premik.smer = STOP;
				}
			}
		}
		this->operator=({ x, y });
	}
	void Sovraznik::naredi() {
		najdiSovraznika();
		if (!mrtev && jaz != -1) {
			sovraznik_kvd = { (float)rd->at(sovrazniki.at(jaz).x1).rdZ, (float)rd->at(sovrazniki.at(jaz).x2).rdZ, ((2.0f / resolucija) * (sovrazniki.at(jaz).x1 + 1)) - 1.0f, ((2.0f / resolucija) * (sovrazniki.at(jaz).x2 + 1)) - 1.0f };
			sovraznik_obl.kvadratRCT(sovraznik_kvd);
			okno->dodajObliko(sovraznik_obl);
		}
		if (!mrtev) {
			premakni();
		}
	}
	void Sovraznik::nastaviResolucijo(int a) {
		resolucija = a;
	}
	void Sovraznik::narisiSeNaMapo() {
		if (rc->mapa->at(yint).at(xint) != znakZaZid && xint <= rc->mapa_x && yint <= rc->mapa_y) {
			rc->mapa->at(yint).at(xint) = sovraznikZastavica;
		}
	}
	Sovraznik::Sovraznik() {
		return;
	}
	Sovraznik::Sovraznik(KOORDINATA k) {
		return;
		this->operator=(k);
		narisiSeNaMapo();
	}
	Sovraznik::Sovraznik(OKNO* okn, RAZDALJE* r, RC* a, KOORDINATA k, string txttra) {
		okno = okn;
		dodajRazdalje(r);
		dodajRC(a);
		this->operator=(k);
		narisiSeNaMapo();
		tekstura = txttra;
		okno->naInit(this->dobiLambdo());
	}
	void Sovraznik::nastaviPotrebneVrednosti(OKNO* okn, RAZDALJE* r, RC* a, KOORDINATA k, string txttra) {
		dodajOkno(okn);
		dodajRazdalje(r);
		dodajRC(a);
		this->operator=(k);
		narisiSeNaMapo();
		tekstura = txttra;
		okno->naInit(this->dobiLambdo());
	}
	KLIC Sovraznik::dobiLambdo() {
		return initTeksturaLambda;
	}
	void Sovraznik::strel(KOORDINATA krd) {
		if ((int)krd.x == xint && (int)krd.y == yint) {
			zdravje -= 5.0f;
		}
		if (!(zdravje > 0.0f)) {
			mrtev = true;
			respwn.Zacni();
			umri();
			zbrisiSeIzMape();
		}
		if (mrtev && respwn.Cas() > respawn.cas) {
			zdravje = zdrav;
			x = respawn.x;
			y = respawn.y;
			narisiSeNaMapo();
			std::cout << "Respawn";
		}
		return;
	}
	void Sovraznik::noRespawn() {
		respawn.cas = -1;
	}
	void Sovraznik::setRespawn(Respawn rp) {
		respawn = rp;
	}
}
