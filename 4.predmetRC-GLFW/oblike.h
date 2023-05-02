#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include "cas.h"
#include "shader.h"
#include "tekstura.h"
#include "verteksi.h"
#include "vecf.h"

namespace igra {
	class OBLIKA;
}
#include "okno.h"

#define GL_QUADS 5
#define INIT true

namespace igra {
	extern int r;

	struct KvadratRCT {
		float r1;
		float r2;
		float x1;
		float x2;
		int ID = 1;
		float stranicaA();
		float stranicaB();
		float kot();
		int orientacija();
	};

	typedef std::vector<KvadratRCT> KvadratiRCT;

	KvadratiRCT operator+ (KvadratiRCT a, KvadratiRCT b);
	KvadratRCT operator+ (KvadratRCT a, KvadratRCT b);
	KvadratRCT operator- (KvadratRCT a, KvadratRCT b);
	KvadratRCT operator/ (KvadratRCT a, float b);
	KvadratiRCT operator* (KvadratiRCT a, KvadratiRCT b);
	void operator++ (KvadratiRCT& a);
	void operator+= (KvadratiRCT& a, KvadratiRCT& b);

	class OBLIKA {
	private:
		bool _Tekstura = true;
		bool _3D = false;
		int kiraOblika = 0;
		char* potTeksture = nullptr;
		BARVA barva = { 1, 1, 1, 1 };
		float _Kot = 60.0f;
		GLfloat vert[32] =
		{ //     COORDINATES     /        COLORS      /   TexCoord  //
			-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
			-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
			 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
			 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
		};

		GLuint indices[6] =
		{
			0, 2, 1, // Upper triangle
			0, 3, 2 // Lower triangle
		};
		GLfloat predPoravnavoVert[32] =
		{ //     COORDINATES     /        COLORS      /   TexCoord  //
			-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
			-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
			 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
			 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
		};
		void poravnajVert();
		SHADER shader;
		TEKSTURA tekstura;
	public:
		float resolucija = 300.0f;
		float velikostMape = 64.0f;
		std::function<void()> Naredi = [&] {
			//naredi();
		};
		void naredi();
		void init();
		void Tekstura(const char* pot);
		void noveKoodrinate(GLfloat ver[32]);
		void nova(const char* pot, GLfloat ver[32]);
		void kvadratRC(float razdalja, float x, bool zastavica);
		void kvadratRCT(KvadratRCT kv, float texvert[8]);
		void kvadratRCT(KvadratRCT kv, vec8f texvert);
		void kvadratRCT(KvadratRCT kv);
		void kvadratX(float x, float sirina);
		void kvadratY(float y, float sirina);
		void crta(float x1, float y1, float x2, float y2, float debelina);
		void kvadrat(float x1, float x2, float y1, float y2);
		void kvadratXY(float x, float y, float XYdolzina);
		void tocka(float x, float y, float sirina);
		void Barva(BARVA br);
		void Kot(float __KOT);
		void Zamik(float a[12]);
		void operator << (BARVA br);
		void operator << (const char* pot);
		void operator << (GLfloat ver[32]);
		void n3D();
		void vertecijiSlike(float a[8]);
		void vertecijiSlike(vec8f a);
		OBLIKA(BARVA br, bool INI_T = false);
		OBLIKA(BARVA br, GLfloat ver[32], bool INI_T = false);
		OBLIKA(const char* pot, bool INI_T = false);
		OBLIKA(const char* pot, GLfloat ver[32], bool INI_T = false);
		OBLIKA(bool INI_T = false);
		~OBLIKA();
	};

	typedef std::vector<OBLIKA> OBLIKE;
	typedef std::vector<OBLIKA*> OBLIKE_ptr;

	void unici_OBLIKE(OBLIKE_ptr& a);
}