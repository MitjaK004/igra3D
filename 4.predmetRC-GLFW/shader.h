#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <thread>
#include <future>
#include "cas.h"
#include "log.h"

namespace igra {
	extern LOG shaderLOG;

	struct BARVA {
		double R = 1;
		double G = 1;
		double B = 1;
		double alfa = 1;
		BARVA(double _R = 1, double _G = 1, double _B = 1, double _A = 1) {
			R = _R;
			G = _G;
			B = _B;
			alfa = _A;
		}
		void rgb(BARVA br = { 1, 1, 1, 1 }) {
			R = br.R;
			G = br.G;
			B = br.B;
			alfa = br.alfa;
		}
		void operator << (BARVA br) {
			R = br.R;
			G = br.G;
			B = br.B;
			alfa = br.alfa;
		}
	};

	std::string dobiVsebinoShadera(std::string imeDatoteke);

	class SHADER
	{
	public:
		GLuint ID;
		SHADER(const char* vertexShaderDatoteka, const char* fragmentShaderDatoteka);
		SHADER(const char* vertexShaderDatoteka, const char* fragmentShaderDatoteka, BARVA br);
		SHADER();
		void kompajlajVertex(GLuint& vertexShader, const char*& vertexKoda, GLuint& ID);
		void kompajlajFragment(GLuint& fragmentShader, const char*& fragmentKoda, GLuint& ID);
		void Aktiviraj();
		void Zbrisi();
	private:
		void soNapake(unsigned int shader, const char* type);
	};


	struct NalozenShader {
		std::string imeDatoteke;
		std::string koda;
	};

	extern std::vector<NalozenShader> nalozeniShaderi;

	extern std::string vsebinaShaderaVert;
	extern std::string vsebinaShaderaInd;
}
