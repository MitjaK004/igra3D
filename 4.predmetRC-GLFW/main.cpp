#include "3D_engine.h"
#include "RC.h"
#include <fstream>
#include <stdlib.h>
#include "Niz.h"
using std::string;
using std::size_t;
using std::ifstream;
using std::stoi;
using std::cout;
using namespace igra;

int main()
{
	STOPARCA sync;

	string conf;

	ifstream config(".config");
	if (config.is_open()) {
		while (!config.eof()) {
			string cnf;
			getline(config, cnf);
			conf += cnf;
		}
	}

	Niz niz = conf;
	VEC_F res;

	res = niz << "resolucija:";
	if (res.at(0) != NIZ_ERR) {
		okno.resolucija = { (int)res.at(0), (int)res.at(1) };
	}

	res = niz << "pozicija:";
	if (res.at(0) != NIZ_ERR) {
		okno.pozicija = { (int)res.at(0), (int)res.at(1) };
	}

	res = niz << "sensitivity:";
	if (res.at(0) != NIZ_ERR) {
		sensitivity = res.at(0);
	}

	res = niz << "stevilo_sovraznikov:";
	if (res.at(0) != NIZ_ERR) {
		steviloSovraznikov = (int)res.at(0);
	}

	init();

	KLIC initTekst = [&] {
		municija.init();
		rezervnaMunicija.init();
		Fps.init();
	};

	okno.naInit(initTekst);

	KLIC fps = [&] {
		FPS = 1.0 / prestanCas();

		if (sync.Cas() > 250) {
			sync.Resetiraj();
			string t1 = okno.i_okna;
			t1 += "  | ";
			string t2 = std::to_string((int)FPS) + " FPS";
			okno.nastaviText(t1 + t2);
			FPS = 0.0f;
			Fps = t2;
		}

		okno << Fps;
	};

	KLIC grafika = [&] {
		generirajOkolje();
	};

	KLIC premikanje = [&] {
		glfwSetInputMode(okno.dobiGLFW_okno(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		preglejMisko();
		preglejTipke();
		gibanje.Resetiraj();
	};

	KLIC orozje = [&] {
		narediSovr();
		narediOrozje();
		streljanje();
		kolkoMunicije();
	};

	okno << fps;
	okno << grafika;
	okno << premikanje;
	okno << orozje;

	//okno.resolucija = {1600, 800};
	//okno.pozicija = { 0, 50 };

	okno.narejiOkno();
	return 0;
}