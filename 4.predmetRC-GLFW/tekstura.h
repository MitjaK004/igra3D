#pragma once

#include <glad/glad.h>
#include <vector>
#include <string>

#include "log.h"
#include "shader.h"

namespace igra {
	extern LOG sll;

	extern std::vector<unsigned char> mipmaps;
	extern const char* mipmap;

	struct NalozenaSlika {
		const char* pot;
		unsigned char* slika;
		int sirinaS, visinaS, kanal;
	};

	extern std::vector<NalozenaSlika> nalozeneSlike;

	class TEKSTURA
	{
	public:
		GLuint ID;
		GLenum tip;
		TEKSTURA(const char* slika, GLenum tipTeksture, GLenum mesto, GLenum format, GLenum pixelType);
		TEKSTURA();

		void nalozi(const char* slika, GLenum tipTeksture, GLenum mesto, GLenum format, GLenum pixelType);
		void dodajShader(SHADER& shader, const char* uniform, GLuint enota);
		void Aktiviraj();
		void Deaktiviraj();
		void Zbrisi();
	};
}