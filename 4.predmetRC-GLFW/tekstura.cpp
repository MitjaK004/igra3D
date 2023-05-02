#include "tekstura.h"

#include <glad/glad.h>
#include <vector>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "log.h"
#include "shader.h"

namespace igra {
	LOG sll("teksture");

	std::vector<unsigned char> mipmaps;
	const char* mipmap;

	std::vector<NalozenaSlika> nalozeneSlike;

	TEKSTURA::TEKSTURA() {

	}

	TEKSTURA::TEKSTURA(const char* slika, GLenum tipTeksture, GLenum mesto, GLenum format, GLenum pixelType)
	{
		nalozi(slika, tipTeksture, mesto, format, pixelType);
	}

	void TEKSTURA::nalozi(const char* slika, GLenum tipTeksture, GLenum mesto, GLenum format, GLenum pixelType) {
		tip = tipTeksture;

		int sirinaS, visinaS, kanal;
		stbi_set_flip_vertically_on_load(true);

		unsigned char* podatki = (unsigned char*)"null";

		for (int c = 0; c < nalozeneSlike.size(); c++) {
			if (nalozeneSlike.at(c).pot == slika) {
				podatki = nalozeneSlike.at(c).slika;
				sirinaS = nalozeneSlike.at(c).sirinaS;
				visinaS = nalozeneSlike.at(c).visinaS;
				kanal = nalozeneSlike.at(c).kanal;
			}
		}
		if (podatki == (unsigned char*)"null") {
			podatki = stbi_load(slika, &sirinaS, &visinaS, &kanal, 0);
			nalozeneSlike.push_back({ slika, podatki, sirinaS, visinaS, kanal });
		}

		STOPARCA stt;

		glGenTextures(1, &ID);
		glActiveTexture(mesto);
		glBindTexture(tipTeksture, ID);

		//glCompressedTexImage2D(tipTeksture, 0, GL_COMPRESSED_RGBA, sirinaS, visinaS, 0, format, podatki);

		glTexParameteri(tipTeksture, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(tipTeksture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(tipTeksture, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(tipTeksture, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(tipTeksture, 0, GL_RGBA, sirinaS, visinaS, 0, format, pixelType, podatki);

		glGenerateMipmap(tipTeksture);

		//stbi_image_free(podatki); Zato ke chacheamo teksure, 
		// se ne smejo izbrisat!!!!

		sll << stt.Koncaj();
		sll++;

		glBindTexture(tipTeksture, 0);
	}

	void TEKSTURA::dodajShader(SHADER& shader, const char* uniform, GLuint enota)
	{
		GLuint texUni = glGetUniformLocation(shader.ID, uniform);
		shader.Aktiviraj();
		glUniform1i(texUni, enota);
	}

	void TEKSTURA::Aktiviraj()
	{
		glBindTexture(tip, ID);
	}

	void TEKSTURA::Deaktiviraj()
	{
		glBindTexture(tip, 0);
	}

	void TEKSTURA::Zbrisi()
	{
		glDeleteTextures(1, &ID);
	}
}