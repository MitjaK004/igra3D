#include <glad/glad.h>
#ifndef VERTEKSI_H
#define VERTEKSI_H

namespace igra {
	class VBO
	{
	public:
		GLuint ID;
		VBO(GLfloat* vertices, GLsizeiptr velikost);
		void Aktiviraj();
		void Deaktiviraj();
		void Zbrisi();
	};

	class VAO
	{
	public:
		GLuint ID;
		VAO();
		void poveziAttrib(VBO& VBO, GLuint postavitev, GLuint stevKomponent, GLenum tip, GLsizeiptr velikost, void* offset);
		void Aktiviraj();
		void Deaktiviraj();
		void Zbrisi();
	};

	class EBO
	{
	public:
		GLuint ID;
		EBO(GLuint* indices, GLsizeiptr velikost);
		void Aktiviraj();
		void Deaktiviraj();
		void Zbrisi();
	};
}

#endif