#include "RC.h"

#include <math.h>
#include "koti.h"
#include <iostream>

namespace igra {
	void RC::initMapa() {
		mapa_x = 0;
		mapa_y = 0;
		for (int i = 0; i < mapa->size(); i++) {
			mapa_x = mapa->at(i).length();
			mapa_y++;
		}
		for (int y = 0; y < mapa_y; y++) {
			for (int x = 0; x < mapa_x; x++) {
				if (mapa->at(y).at(x) != 'zid') {
					legalne_vrednosti.push_back({ (double)x, (double)y });
				}
			}
		}
		std::cout << legalne_vrednosti.size() << '\n';
	}

	void RC::dodajMapo(MAPA* mp) {
		mapa = mp;
	}

	char RC::prnt(double x, double y) {
		int _x = (int)x;
		int _y = (int)y;
		return mapa->at(_y).at(_x);
	}

	void RC::operator<<(MAPA* mp) {
		dodajMapo(mp);
	}

	void RC::izracunajRazdalje(RAZDALJE &zarki) {
		if (!initM) {
			initMapa();
			initM = true;
		}

		if (zarki.size() > 0) {
			zarki.clear();
		}
		double dodaniKot = (2 * FOV) / steviloZarkov;
		double kotPrvegaZarka = FOV + smerPogleda;

		for (int z = 0; z < steviloZarkov; z++) {
			//double kotZarka = (smerPogleda - (FOV / 2.0)) + ((double)z / (double)steviloZarkov) * FOV;
			double kotZarka = kotPrvegaZarka - (z * dodaniKot);

			if (kotZarka > 2 * PI) {
				kotZarka -= 2 * PI;
			}
			else if (kotZarka < 0) {
				kotZarka += 2 * PI;
			}

			bool vdariSteno = false;
			bool vdariMejo = false;

			double korak = 0.1;
			double razdaljaDoZida = 0.0;

			double preveriX = sinf(kotZarka);
			double preveriY = cosf(kotZarka);

			bool prisoSemDoKonca = false;

			char zastavica = 0;

			double rdZ = -1;
			double xZ = -1;
			double yZ = -1;

			while (!vdariSteno && vdariMejo < RD) {
				razdaljaDoZida += korak;

				if (kotZarka > 0 && kotZarka < PI / 2.0) {
					preveriX = pX + sqrt(pow(razdaljaDoZida, 2) - pow((cos(kotZarka) * razdaljaDoZida), 2));
					preveriY = pY + sqrt(pow(razdaljaDoZida, 2) - pow((sin(kotZarka) * razdaljaDoZida), 2));
				}
				else if (kotZarka > PI / 2.0 && kotZarka < PI) {
					preveriX = pX + sqrt(pow(razdaljaDoZida, 2) - pow((cos(kotZarka) * razdaljaDoZida), 2));
					preveriY = pY - sqrt(pow(razdaljaDoZida, 2) - pow((sin(kotZarka) * razdaljaDoZida), 2));
				}
				else if (kotZarka > PI && kotZarka < 3 * (PI / 2)) {
					preveriX = pX - sqrt(pow(razdaljaDoZida, 2) - pow((cos(kotZarka) * razdaljaDoZida), 2));
					preveriY = pY - sqrt(pow(razdaljaDoZida, 2) - pow((sin(kotZarka) * razdaljaDoZida), 2));
				}
				else if (kotZarka > 3 * (PI / 2) && kotZarka < 2 * PI) {
					preveriX = pX - sqrt(pow(razdaljaDoZida, 2) - pow((cos(kotZarka) * razdaljaDoZida), 2));
					preveriY = pY + sqrt(pow(razdaljaDoZida, 2) - pow((sin(kotZarka) * razdaljaDoZida), 2));
				}

				if (preveriX < 0 || preveriX >= mapa_x || preveriY < 0 || preveriY >= mapa_y) {
					vdariSteno = true;
					razdaljaDoZida = RD;
				}
				else {
					if (prnt(preveriX, preveriY) == zid) {
						vdariSteno = true;
					}
					else {
						for (int c = 0; c < objekti.size(); c++) {
							if (objekti.at(c) == prnt(preveriX, preveriY)) {
								zastavica = objekti.at(c);
								xZ = preveriX;
								yZ = preveriY;
								rdZ = razdaljaDoZida;
								break;
							}
						}
					}
				}

			}

			bool zid = false;
			if ((double(preveriX - (int)preveriX) > 0.9 || double(preveriX - (int)preveriX) < 0.1) && (double(preveriY - (int)preveriY) > 0.9 || double(preveriY - (int)preveriY) < 0.1)) {
				zid = true;
			}
			double k = preveriKot(cos(smerPogleda - kotZarka));
			zarki.push_back({ preveriX, preveriY, razdaljaDoZida * k, zid, zastavica, xZ, yZ, rdZ });
		}
		return;
	}

	KOORDINATA RC::prikaziSmer(double razdaljaDoZida, double kot) {
		KOORDINATA krd;
		double rotacija = smerPogleda;
		if (rotacija < 0) {
			rotacija += 2 * PI;
		}
		if (rotacija > 2 * PI) {
			rotacija -= 2 * PI;
		}
		double kotZarka = rotacija + kot, preveriX = 1, preveriY = 1;
		if (kotZarka < 0) {
			kotZarka += 2 * PI;
		}
		if (kotZarka > 2 * PI) {
			kotZarka -= 2 * PI;
		}
		if (kotZarka > 0 && kotZarka < PI / 2.0) {
			preveriX = pX + sqrt(pow(razdaljaDoZida, 2) - pow((cos(kotZarka) * razdaljaDoZida), 2));
			preveriY = pY + sqrt(pow(razdaljaDoZida, 2) - pow((sin(kotZarka) * razdaljaDoZida), 2));
		}
		else if (kotZarka > PI / 2.0 && kotZarka < PI) {
			preveriX = pX + sqrt(pow(razdaljaDoZida, 2) - pow((cos(kotZarka) * razdaljaDoZida), 2));
			preveriY = pY - sqrt(pow(razdaljaDoZida, 2) - pow((sin(kotZarka) * razdaljaDoZida), 2));
		}
		else if (kotZarka > PI && kotZarka < 3 * (PI / 2)) {
			preveriX = pX - sqrt(pow(razdaljaDoZida, 2) - pow((cos(kotZarka) * razdaljaDoZida), 2));
			preveriY = pY - sqrt(pow(razdaljaDoZida, 2) - pow((sin(kotZarka) * razdaljaDoZida), 2));
		}
		else if (kotZarka > 3 * (PI / 2) && kotZarka < 2 * PI) {
			preveriX = pX - sqrt(pow(razdaljaDoZida, 2) - pow((cos(kotZarka) * razdaljaDoZida), 2));
			preveriY = pY + sqrt(pow(razdaljaDoZida, 2) - pow((sin(kotZarka) * razdaljaDoZida), 2));
		}
		krd.x = preveriX;
		krd.y = preveriY;
		if (debug == true) {
			system("cls");
			std::cout << krd.x << " | " << krd.y << "\nKot: "
				<< kotZarka << '\n';
		}
		return krd;
	}

	void RC::premikNaprej(double hitrost = 0.1) {
		KOORDINATA k = prikaziSmer(hitrost);

		if (pX > 0 && pY > 0 && pX < mapa_x && pY < mapa_y) {
			if (prnt(k.x, k.y) != zid) {
				pX = k.x;
				pY = k.y;
			}
		}
	}

	void RC::premikNazaj(double hitrost = 0.1) {
		KOORDINATA k = prikaziSmer(hitrost, PI);

		if (pX > 0 && pY > 0 && pX < mapa_x && pY < mapa_y) {
			if (prnt(k.x, k.y) != zid) {
				pX = k.x;
				pY = k.y;
			}
		}
	}

	void RC::premikLevo(double hitrost = 0.1) {
		KOORDINATA k = prikaziSmer(hitrost, PI / 2.0);

		if (pX > 0 && pY > 0 && pX < mapa_x && pY < mapa_y) {
			if (prnt(k.x, k.y) != zid) {
				pX = k.x;
				pY = k.y;
			}
		}
	}

	void RC::premikDesno(double hitrost = 0.1) {
		KOORDINATA k = prikaziSmer(hitrost, -(PI / 2.0));

		if (pX > 0 && pY > 0 && pX < mapa_x && pY < mapa_y) {
			if (prnt(k.x, k.y) != zid) {
				pX = k.x;
				pY = k.y;
			}
		}
	}

	KOORDINATA RC::vstreli() {
		KOORDINATA k;

		float max = 0.0f;

		for (float c = 0.0f; c < 10.0f; c += 0.1f) {
			k = prikaziSmer(c);
			if (prnt(k.x, k.y) == '#') {
				max = c;
				break;
			}
		}

		for (int i = 0; i < objekti.size(); i++) {
			for (float c = 0.0f; c < max; c += 0.1f) {
				k = prikaziSmer(c);

				if (objekti.size() > 0 && prnt(k.x, k.y) == objekti.at(i)) {
					//mapa->at((int)k.y).at((int)k.x) = ' ';
					break;
				}
			}
		}

		return k;
	}
	bool RC::legalna(KOORDINATA k) {
		bool ret = false;
		for (int c = 0; c < legalne_vrednosti.size(); c++) {
			if ((int)k.x == (int)legalne_vrednosti.at(c).x && (int)k.y == (int)legalne_vrednosti.at(c).y && prnt(k.x, k.y) != zid) {
				ret = true;
			}
			//std::cout << c << ", " << ((ret)?"true":"false") << '\n';
		}
		return ret;
	}
}