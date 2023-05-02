#pragma once
#include <string>
#include <vector>
#include <functional>
#include "oblike.h"
#include "Tekst.h"
#include <memory>
#include <thread>
#include <future>

namespace igra {
	typedef std::vector<OBLIKA> OBLIKE;
	typedef std::vector<OBLIKA*> OBLIKE_ptr;

	typedef std::vector<std::function<void()>> KLICI;

	struct RESOLUCIJA {
		int dolzina;
		int sirina;
	};

	struct POZICIJA {
		int x;
		int y;
	};

	extern STOPARCA stdStp;

	void zacniStopat();
	float nehajStopat();
	float zracunajPovprecje();

	extern float(*hejajStopat)();

	class OKNO
	{
	public:
		OKNO(std::string imeOkna);
		~OKNO();
		std::string i_okna = "ime_okna";
		RESOLUCIJA resolucija = { 1920, 1080 };
		POZICIJA pozicija = { 0, 0 };
		void narejiOkno();
		void dodajObliko(OBLIKA& oblika);
		void dodajObliko_ptr(OBLIKA* oblika);
		void dodajKlic(KLIC klic);
		void nastaviText(std::string text);
		double koeficientY();
		double koeficientX();
		void operator<<(KLIC klic);
		void operator<<(OBLIKA* oblika);
		void operator<<(OBLIKA& oblika);
		void operator<<(RESOLUCIJA rs);
		void operator<<(Tekst &t);
		GLFWwindow* dobiGLFW_okno();
		void naInit(KLIC lambda);
	private:
		GLFWwindow* okno;
		OBLIKE oblike;
		std::vector<Tekst> teksti;
		OBLIKE_ptr oblikePtr;
		KLICI klicNazaj;
		OBLIKA* chache = nullptr;
		std::vector<KLIC> initLambde;
		void izvediVseKlice();
		void narisiVseOblike();
		void narisiVseTekste();
		void init();
	};
}