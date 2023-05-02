#include "okno.h"
#include <string>
#include <vector>
#include <functional>
#include "oblike.h"
#include <memory>
#include <thread>
#include <future>

namespace igra {
	STOPARCA stdStp = { true };

	void zacniStopat() {
		stdStp.Zacni();
	}

	float nehajStopat() {
		return stdStp.Koncaj();
	}

	float zracunajPovprecje() {
		return stdStp.Povprecje();
	}

	float(*hejajStopat)() = nehajStopat;

	OKNO::OKNO(std::string imeOkna)
	{
		i_okna = imeOkna;
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	OKNO::~OKNO()
	{

	}

	void OKNO::operator << (KLIC klic) {
		dodajKlic(klic);
	}

	void OKNO::operator << (OBLIKA* oblika) {
		dodajObliko_ptr(oblika);
	}

	void OKNO::operator << (OBLIKA& oblika) {
		dodajObliko(oblika);
	}

	void OKNO::narejiOkno() {
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		okno = glfwCreateWindow(resolucija.dolzina, resolucija.sirina, i_okna.c_str(), NULL, NULL);
		glfwSetWindowPos(okno, pozicija.x, pozicija.y);
		glfwShowWindow(okno);
		if (okno == NULL)
		{
			std::cout << "napaka pri nastanku okna" << std::endl;
			glfwTerminate();
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_LOSE_CONTEXT_ON_RESET);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_FLUSH);

		glfwMakeContextCurrent(okno);
		gladLoadGL();
		glViewport(0, 0, resolucija.dolzina, resolucija.sirina);

		glfwSwapInterval(0);

		init();

		while (!glfwWindowShouldClose(okno))
		{
			glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			
			zacniStopat();
			narisiVseOblike();
			hejajStopat();
			narisiVseTekste();
			izvediVseKlice();
			
			glfwSwapBuffers(okno);
			glfwPollEvents();
			
		}

		glfwDestroyWindow(okno);
		glfwTerminate();
		return;
	}

	void OKNO::dodajObliko(OBLIKA& oblika) {
		oblike.push_back(oblika);
	}

	void OKNO::dodajKlic(KLIC klic) {
		klicNazaj.push_back(klic);
	}

	void OKNO::izvediVseKlice() {
		for (int c = 0; c < klicNazaj.size(); c++) {
			klicNazaj.at(c)();
		}
	}

	void OKNO::narisiVseOblike() {
		int sz = oblike.size();
		for (int c = 0; c < oblike.size(); c++) {
			oblike.at(c).naredi();
		}
		oblike.clear();
		for (int c = 0; c < oblikePtr.size(); c++) {
			oblikePtr.at(c)->naredi();
		}
		oblikePtr.clear();
	}

	double OKNO::koeficientX() {
		double k = 200 / double(resolucija.sirina);
		k /= 100;
		return k;
	}

	double OKNO::koeficientY() {
		double k = 200 / double(resolucija.dolzina);
		k /= 100;
		return k;
	}

	void OKNO::nastaviText(std::string text) {
		glfwSetWindowTitle(okno, text.c_str());
		//nic se
	}

	void OKNO::dodajObliko_ptr(OBLIKA* oblika) {
		oblikePtr.push_back(oblika);
	}

	GLFWwindow* OKNO::dobiGLFW_okno() {
		return okno;
	}

	void OKNO::operator<<(RESOLUCIJA rs) {
		resolucija = rs;
	}

	void OKNO::operator<<(Tekst& t) {
		teksti.push_back(t);
	}

	void OKNO::narisiVseTekste() {
		for (int c = 0; c < teksti.size(); c++) {
			teksti.at(c).naredi();
		}
		teksti.clear();
	}

	void OKNO::naInit(KLIC lambda) {
		initLambde.push_back(lambda);
	}

	void OKNO::init() {
		for (auto a : initLambde) {
			a();
		}
	}
}