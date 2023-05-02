#pragma once
#include "okno.h"
#include <iostream>
#include <chrono>
#include <sstream>
#include <fstream>
#include <memory>
#include <thread>
#include <future>
#include "log.h"
#include "RC.h"
#include "oblike.h"
#include <vector>

namespace igra {
	extern OKNO okno;
	extern GLFWwindow* GLFW_okno;
	extern RC metalec_zarkov;
	extern OBLIKA tla;
	extern OBLIKA strop;
	extern OBLIKE Stene;
	extern LOG log;
	extern RAZDALJE rd;
	extern MAPA mapa;
	extern STOPARCA gibanje;
	extern OBLIKA orozje;

	extern bool capCur;
	extern int resolucija;
	extern bool tek;
	extern float hitrostGibanja;
	extern bool streljam;
	extern int steviloSovraznikov;

	extern float FPS;
	extern Tekst Fps;

	extern float sensitivity;

	extern unsigned short sarzer;
	extern Tekst municija;
	extern Tekst rezervnaMunicija;

	extern std::chrono::system_clock::time_point tp1;
	extern std::chrono::system_clock::time_point tp2;
	
	void init();

	float prestanCas();
	void narediStene(RAZDALJE& rd, KvadratiRCT& stene, int zacetek, int konec, bool zastavica, int id);
	void generirajOkolje();
	void preglejMisko();
	void preglejTipke();
	void narediPogled(float kot);
	void narediOrozje();
	void streljanje();
	void kolkoMunicije();
	void narediSovr();
}