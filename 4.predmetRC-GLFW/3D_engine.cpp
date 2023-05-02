#include <iostream>
#include <chrono>
#include <sstream>
#include <fstream>
#include <memory>
#include <thread>
#include <future>
#include "log.h"
#include "3D_engine.h"
#include "RC.h"
#include "oblike.h"
#include "okno.h"
#include <vector>
#include <irrklang/irrKlang.h>
#include "animacija.h"
#include "Sovraznik.h"
#include <stdlib.h>


namespace igra {
	OKNO okno("POSTAR OFENSIVE");
	GLFWwindow* GLFW_okno;
	RC metalec_zarkov;
	OBLIKA tla({ 0.54, 0.27, 0.1 });
	OBLIKA strop({ 0.15, 0.09, 0.7 });
	OBLIKE Stene;
	LOG log("debug");
	RAZDALJE rd;
	MAPA mapa = {
		"#################################################",
		"#               #               #               #",
		"#               #               #               #",
		"########        #               #       #       #",
		"#                    #          #       #       #",
		"#        #           #          #       #       #",
		"#        #           #          #       #       #",
		"#        #           #                  #       #",
		"#        #           #                  #       #",
		"#################################################"
	};
	STOPARCA gibanje;
	OBLIKA orozje("M16.png");
	irrklang::ISoundEngine* SoundEngine = irrklang::createIrrKlangDevice();
	STOPARCA streljam_stoparca;
	ANIMACIJA reloadAnim;
	irrklang::ISound* tmpZ = nullptr;
	Sovraznik joze;
	Sovraznik stanko;
	Sovraznik* sovrazniki = nullptr;
	int steviloSovraznikov = 10;

	bool je_sovr = false;
	OBLIKA sovr("sovr.png");

	KLIC initObl = [&] {
		sovr.init();
		tla.init();
		strop.init();
		orozje.init();
	};

	bool capCur = true;
	bool tek = false;
	int resolucija = 300;
	float hitrostGibanja = 5.0f;
	bool streljam = false;
	bool reloadam = false;

	float FPS = 0;
	Tekst Fps(std::to_string(FPS));

	unsigned short rezerva = 1500;
	unsigned short sarzer = 30;
	Tekst municija(std::to_string(sarzer));
	Tekst rezervnaMunicija(std::to_string(rezerva));

	float sensitivity = 1.9f;
	float ziv = 100.0f;

	std::chrono::system_clock::time_point tp1 = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point tp2 = std::chrono::system_clock::now();

	void init() {
		metalec_zarkov << &mapa;
		metalec_zarkov.debug = false;
		metalec_zarkov.objekti.push_back('$');
		strop.kvadratY(0.5, 1);
		tla.kvadratY(-0.5, 1);
		municija.x = 720.0f;
		municija.y = 555.0f;
		municija.scale = 0.5f;
		municija.color = glm::vec3(1, 0, 0);
		rezervnaMunicija.x = 750.0f;
		rezervnaMunicija.y = 555.0f;
		rezervnaMunicija.scale = 0.5f;
		rezervnaMunicija.color = glm::vec3(1, 0, 0);
		Fps.x = 7.0f;
		Fps.y = 565.0f;
		Fps.scale = 0.37f;
		//municija.init();
		okno.naInit(initObl);

		reloadAnim << &orozje;
		vec4f vert;

		vert[0] = 0.384f;
		vert[1] = 0.384f;
		vert[2] = 0.52f;
		vert[3] = 0.52f;

		reloadAnim += vert;


		vert[2] = 0.625f;
		vert[3] = 0.625f;
		vert[0] = 0.52f;
		vert[1] = 0.52f;

		reloadAnim += vert;


		vert[2] = 0.75f;
		vert[3] = 0.75f;
		vert[0] = 0.625f;
		vert[1] = 0.625f;

		reloadAnim += vert;


		vert[2] = 0.875f;
		vert[3] = 0.875f;
		vert[0] = 0.75f;
		vert[1] = 0.75f;

		reloadAnim += vert;

		
		vert[2] = 1.0f;
		vert[3] = 1.0f;
		vert[0] = 0.875f;
		vert[1] = 0.875f;

		reloadAnim += vert;
		reloadAnim.Trajanje(900);

		joze.nastaviPotrebneVrednosti(&okno, &rd, &metalec_zarkov, { 13, 7 });
		joze.nastaviPremik({0.008f, X, true, 1});

		stanko.nastaviPotrebneVrednosti(&okno, &rd, &metalec_zarkov);

		if (sovrazniki == nullptr && steviloSovraznikov > 0) {
			sovrazniki = new Sovraznik[steviloSovraznikov];
		}

		for (int c = 0; c < steviloSovraznikov; c++) {
			int x = 2;
			int y = 2;
			do {
				x = rand() % mapa.at(0).length();
				y = rand() % mapa.size();
			} while (mapa.at(y).at(x) != ' ');
			sovrazniki[c].nastaviPotrebneVrednosti(&okno, &rd, &metalec_zarkov, { (double)x, (double)y });
		}
	}

	float prestanCas() {
		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> prC = tp2 - tp1;
		tp1 = tp2;
		float _prestanCas = prC.count();
		return _prestanCas;
	}

	void narediStene(RAZDALJE& rd, KvadratiRCT& stene, int zacetek, int konec, bool zid = true, int id = 1) {
		int oblikaC = 0;
		float x1 = 0.0f, r1 = -1.0f;
		bool prejsnjizid = zid;
		float prejX = -1, prejY = -1, mX = -1, mRD = -1;
		bool mhm = false;
		for (int c = zacetek; c < konec; c++) {
			mhm = false;
			KvadratRCT tmp = { r1, rd.at(c).razdalja, x1, ((2.0f / resolucija) * (c + 1)) - 1.0, id };
			if (r1 != -1.0f && abs(rd.at(c).x - prejX) > 0.1f && abs(rd.at(c).y - prejY) > 0.1f) {
				tmp = { r1, mRD, x1, mX };
				r1 = -1.0f;
				stene.push_back(tmp);
				prejsnjizid = !prejsnjizid;
			}
			else if (prejsnjizid != rd.at(c).zid) {
				mhm = true;
				prejsnjizid = rd.at(c).zid;
				if (r1 == -1.0f) {
					x1 = ((2.0f / resolucija) * (c + 1)) - 1.0;
					r1 = rd.at(c).razdalja;
				}
				else {
					r1 = -1.0f;
					stene.push_back(tmp);
				}
			}
			else if (c == konec - 1) {
				prejsnjizid = rd.at(c).zid;
				if (r1 != -1.0f) {
					r1 = -1.0f;
					stene.push_back(tmp);
				}
			}
			prejX = rd.at(c).x;
			prejY = rd.at(c).y;
			mRD = rd.at(c).razdalja;
			mX = ((2.0f / resolucija) * (c + 2)) - 1.0;
		}
		return;
	}

	void popraviVmesne(KvadratiRCT& a, int ID_vlke, int ID_male) {
		for (int c = 0; c < a.size(); c+=2) {
			if (c + 1 < a.size()) {
				if (abs(a.at(c).x1 - a.at(c).x2) > abs(a.at(c+1).x1 - a.at(c+1).x2)) {
					a.at(c).ID = ID_vlke;
					a.at(c+1).ID = ID_male;
				}
				else if (abs(a.at(c).x1 - a.at(c).x2) < abs(a.at(c + 1).x1 - a.at(c + 1).x2)) {
					a.at(c+1).ID = ID_vlke;
					a.at(c).ID = ID_male;
				}
			}
			else {
				if (abs(a.at(c).x1 - a.at(c).x2) > abs(a.at(c - 1).x1 - a.at(c - 1).x2)) {
					a.at(c).ID = ID_vlke;
					a.at(c - 1).ID = ID_male;
				}
				else if (abs(a.at(c).x1 - a.at(c).x2) < abs(a.at(c - 1).x1 - a.at(c - 1).x2)) {
					a.at(c - 1).ID = ID_vlke;
					a.at(c).ID = ID_male;
				}
			}
		}
	}

	void generirajOkolje() {
		metalec_zarkov.steviloZarkov = resolucija;
		metalec_zarkov.izracunajRazdalje(rd);
		double tlaK = -(1.0 / 100.0);
		double stropK = -tlaK;
		BARVA barva = { 0.01, 0.004, 0, 1 };

		okno << tla;
		okno << strop;

		log.NoviFrame();
		STOPARCA tt;
		tt.Zacni();

		KvadratiRCT stene;
		KvadratiRCT vmesne;

		log << tt.Koncaj();

		narediStene(rd, stene, 0, resolucija, true, 1);
		narediStene(rd, vmesne, 0, resolucija, false, 1);

		stene += vmesne;

		int stenaC = -1;
		for (int c = 0; c < stene.size(); c++) {
			if (stene.at(c).ID == 1) {
				stenaC++;
				if (stenaC >= Stene.size()) {
					//pd.stene.push_back(new OBLIKA({ 1, 0.2, 0.2 }));
					Stene.push_back(OBLIKA("wall.png", INIT));
				}
				else {
					Stene.at(stenaC).Tekstura("wall.png");
				}
				Stene.at(stenaC).resolucija = resolucija;
				Stene.at(stenaC).kvadratRCT(stene.at(c));
				okno << Stene.at(stenaC);
			}
			else if (stene.at(c).ID == 2) {//2 je za vmesne
				stenaC++;
				if (stenaC >= Stene.size()) {
					Stene.push_back(OBLIKA("wall.png", INIT));
				}
				else {
					float vertimg[8]{
						0.0f, 0.5f,
						0.0f, 0.0f,
						0.166f, 0.5f,
						0.166f, 0.0f,
					};

					Stene.at(stenaC).Tekstura("wall.png");
					Stene.at(stenaC).vertecijiSlike(vertimg);
				}
				float vert[8] = {
					0.0f, 0.0f,
					0.0f, 0.5f,
					0.5f, 0.5f,
					0.5f, 0.0f
				};
				Stene.at(stenaC).resolucija = resolucija;
				Stene.at(stenaC).kvadratRCT(stene.at(c));
				okno << Stene.at(stenaC);
			}
		}
	}

	struct Miska {
		double x;
		double y;
	};

	void preglejMisko() {
		if (capCur == true) {
			Miska miska;
			Miska defolt = { 800, 400 };
			GLFW_okno = okno.dobiGLFW_okno();
			glfwGetCursorPos(GLFW_okno, &miska.x, &miska.y);
			miska.x -= defolt.x;
			miska.y -= defolt.y;
			if (miska.x != 0 && miska.y != 0) {
				if (miska.x < 0) {
					narediPogled(metalec_zarkov.smerPogleda + (sensitivity * (gibanje.Cas() / 1000.0f)));
					glfwSetCursorPos(GLFW_okno, defolt.x, defolt.y);
				}
				else if (miska.x > 0) {
					narediPogled(metalec_zarkov.smerPogleda - (sensitivity * (gibanje.Cas() / 1000.0f)));
					glfwSetCursorPos(GLFW_okno, defolt.x, defolt.y);
				}
				else if (miska.x < 100) {
					narediPogled(metalec_zarkov.smerPogleda + (2 * sensitivity * (gibanje.Cas() / 1000.0f)));
					glfwSetCursorPos(GLFW_okno, defolt.x, defolt.y);
				}
				else if (miska.x > 100) {
					narediPogled(metalec_zarkov.smerPogleda - (2 * sensitivity * (gibanje.Cas() / 1000.0f)));
					glfwSetCursorPos(GLFW_okno, defolt.x, defolt.y);
				}
				else if (miska.x < 300) {
					narediPogled(metalec_zarkov.smerPogleda + (4 * sensitivity * (gibanje.Cas() / 1000.0f)));
					glfwSetCursorPos(GLFW_okno, defolt.x, defolt.y);
				}
				else if (miska.x > 300) {
					narediPogled(metalec_zarkov.smerPogleda - (4 * sensitivity * (gibanje.Cas() / 1000.0f)));
					glfwSetCursorPos(GLFW_okno, defolt.x, defolt.y);
				}
				else if (miska.x < 400) {
					narediPogled(metalec_zarkov.smerPogleda + (10 * sensitivity * (gibanje.Cas() / 1000.0f)));
					glfwSetCursorPos(GLFW_okno, defolt.x, defolt.y);
				}
				else if (miska.x > 400) {
					narediPogled(metalec_zarkov.smerPogleda - (10 * sensitivity * (gibanje.Cas() / 1000.0f)));
					glfwSetCursorPos(GLFW_okno, defolt.x, defolt.y);
				}
			}
		}
	}

	void narediPogled(float kot) {
		if (kot < 0) {
			kot += 2 * PI;
		}
		else if (kot > 2 * PI) {
			kot -= 2 * PI;
		}
		metalec_zarkov.smerPogleda = kot;
	}

	void preglejTipke() {
		if (glfwGetKey(okno.dobiGLFW_okno(), GLFW_KEY_W) == GLFW_PRESS) {
			preglejMisko();
			if (glfwGetKey(okno.dobiGLFW_okno(), GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS) {
				metalec_zarkov.premikNaprej(2 * (hitrostGibanja * (gibanje.Cas() / 1000.0f)));
			}
			else {
				metalec_zarkov.premikNaprej(4 * (hitrostGibanja * (gibanje.Cas() / 1000.0f)));
			}
		}
		if (glfwGetKey(okno.dobiGLFW_okno(), GLFW_KEY_S) == GLFW_PRESS) {
			preglejMisko();
			metalec_zarkov.premikNazaj(hitrostGibanja * (gibanje.Cas() / 1000.0f));
		}
		if (glfwGetKey(okno.dobiGLFW_okno(), GLFW_KEY_A) == GLFW_PRESS) {
			preglejMisko();
			metalec_zarkov.premikLevo(hitrostGibanja * (gibanje.Cas() / 1000.0f));
		}
		if (glfwGetKey(okno.dobiGLFW_okno(), GLFW_KEY_D) == GLFW_PRESS) {
			preglejMisko();
			metalec_zarkov.premikDesno(hitrostGibanja * (gibanje.Cas() / 1000.0f));
		}
		if (glfwGetKey(okno.dobiGLFW_okno(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			capCur = !capCur;
		}
	}

	void narediOrozje() {
		orozje.kvadratXY(-0.35f, -0.35f, 0.7f);
		
		vec8f vert = {
			0.0f, 0.0f,
			0.0f, 1.0f,
			0.125f, 1.0f,
			0.125f, 0.0f
		};

		if (streljam == true && streljam_stoparca.Cas() < 15.0f) {
			vert[4] = 0.250f;
			vert[6] = 0.250f;

			vert[0] = 0.125f;
			vert[2] = 0.125f;
		}
		if (streljam == true && streljam_stoparca.Cas() > 15.0f) {
			vert[4] = 0.375f;
			vert[6] = 0.375f;

			vert[0] = 0.250f;
			vert[2] = 0.250f;
		}
		/*
		if (reloadam == true && reloadam_stoparca.Cas() < 200.0f) {
			vert[4] = 0.52f;
			vert[6] = 0.52f;

			vert[0] = 0.384f;
			vert[2] = 0.384f;
		}
		if (reloadam == true && reloadam_stoparca.Cas() > 200.0f && reloadam_stoparca.Cas() < 400.0f) {
			vert[4] = 0.625f;
			vert[6] = 0.625f;

			vert[0] = 0.52f;
			vert[2] = 0.52f;
		}
		if (reloadam == true && reloadam_stoparca.Cas() > 400.0f && reloadam_stoparca.Cas() < 600.0f) {
			vert[4] = 0.75f;
			vert[6] = 0.75f;

			vert[0] = 0.625f;
			vert[2] = 0.625f;
		}
		if (reloadam == true && reloadam_stoparca.Cas() > 600.0f && reloadam_stoparca.Cas() < 800.0f) {
			vert[4] = 0.875f;
			vert[6] = 0.875f;

			vert[0] = 0.75f;
			vert[2] = 0.75f;
		}
		if (reloadam == true && reloadam_stoparca.Cas() > 800.0f && reloadam_stoparca.Cas() < 1000.0f) {
			vert[4] = 1.0f;
			vert[6] = 1.0f;

			vert[0] = 0.875f;
			vert[2] = 0.875f;
		}*/
		if (reloadam) {
			reloadAnim();
		}
		else {
			orozje.vertecijiSlike(vert);
		}
		okno << orozje;
	}

	void streljanje() {
		if (streljam_stoparca.Cas() > 30.0f) {
			streljam = false;
			streljam_stoparca.Koncaj();
		}
		if (!reloadAnim.Animiram() && reloadam) {
			reloadam = false;
			if (rezerva > 0 && rezerva > 30) {
				rezerva -= 30;
				sarzer = 30;
			}
			else if (rezerva > 0 && rezerva <= 30) {
				sarzer = rezerva;
				rezerva = 0;
			}
		}
		if (glfwGetMouseButton(okno.dobiGLFW_okno(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			if (!SoundEngine->isCurrentlyPlaying("M16.mp3") && streljam == false && sarzer != 0 && !reloadam) {
				sarzer--;
				streljam = true;
				SoundEngine->play2D("M16.mp3", false);
				streljam_stoparca.Zacni();
				KOORDINATA k = metalec_zarkov.vstreli();
				mapa.at(k.y).at(k.x) = ' ';
				joze.strel(k);
				stanko.strel(k);
				for (int c = 0; c < steviloSovraznikov; c++) {
					sovrazniki[c].strel(k);
				}
			}
			if (sarzer == 0 && !reloadam) {
				reloadam = true;
			}
		}
		if (glfwGetKey(okno.dobiGLFW_okno(), GLFW_KEY_R) == GLFW_PRESS && !reloadam) {
			//tmpZ =  SoundEngine->play2D("M16R.mp3", false);
			reloadam = true;
		}
		if (tmpZ) {
			tmpZ->setPlaybackSpeed(0.0001f);
		}
	}

	void kolkoMunicije() {
		municija = std::to_string(sarzer);
		okno << municija;
		rezervnaMunicija = std::to_string(rezerva);
		okno << rezervnaMunicija;
	}

	bool naprej = true;
	void narediSovr() {
		stanko.naredi();
		joze.naredi();
		for (int c = 0; c < steviloSovraznikov; c++) {
			sovrazniki[c].naredi();
		}
		return;
	}
}