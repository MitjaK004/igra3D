#pragma once
#include "Tekst.h"
#include <iostream>
#include <map>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "shader.h"

namespace igra {
	struct CRKA {
		unsigned int TextureID;
		glm::ivec2   Size;     
		glm::ivec2   Bearing;  
		unsigned int Advance;  
	};

	class Tekst
	{
	private:
		std::string tekst;
		std::map<GLchar, CRKA> crke;
		unsigned int VAO, VBO;
		const unsigned int SCR_WIDTH = 800;
		const unsigned int SCR_HEIGHT = 600;
		float _x = 700.0f, _y = 500.0f, _scale = 1.0f;
		SHADER shader;
	public:
		float x = 700.0f, y = 500.0f, scale = 1.0f;
		glm::vec3 color = glm::vec3(0.5, 0.8f, 0.2f);
		Tekst(std::string a);
		void operator= (std::string a);
		void init();
		void naredi();
	};
}