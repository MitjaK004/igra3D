#include "verteksi.h"

namespace igra {
	VBO::VBO(GLfloat* vertices, GLsizeiptr velikost)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, velikost, vertices, GL_STATIC_DRAW);
	}

	void VBO::Aktiviraj()
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	void VBO::Deaktiviraj()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VBO::Zbrisi()
	{
		glDeleteBuffers(1, &ID);
	}



	VAO::VAO()
	{
		glGenVertexArrays(1, &ID);
	}

	void VAO::poveziAttrib(VBO& VBO, GLuint postavitev, GLuint stevKomponent, GLenum tip, GLsizeiptr velikost, void* offset)
	{
		VBO.Aktiviraj();
		glVertexAttribPointer(postavitev, stevKomponent, tip, GL_FALSE, velikost, offset);
		glEnableVertexAttribArray(postavitev);
		VBO.Deaktiviraj();
	}

	void VAO::Aktiviraj()
	{
		glBindVertexArray(ID);
	}

	void VAO::Deaktiviraj()
	{
		glBindVertexArray(0);
	}

	void VAO::Zbrisi()
	{
		glDeleteVertexArrays(1, &ID);
	}


	EBO::EBO(GLuint* indices, GLsizeiptr velikost)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, velikost, indices, GL_STATIC_DRAW);
	}

	void EBO::Aktiviraj()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}

	void EBO::Deaktiviraj()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void EBO::Zbrisi()
	{
		glDeleteBuffers(1, &ID);
	}
}