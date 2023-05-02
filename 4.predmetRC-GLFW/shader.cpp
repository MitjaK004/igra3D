#include "shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
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
	LOG shaderLOG("shader");

	std::vector<NalozenShader> nalozeniShaderi;

	std::string vsebinaShaderaVert = "N";
	std::string vsebinaShaderaInd = "N";

	std::string dobiVsebinoShadera(std::string imeDatoteke)
	{
		std::string vsebina = "null";
		for (int c = 0; c < nalozeniShaderi.size(); c++) {
			if (nalozeniShaderi.at(c).imeDatoteke == imeDatoteke) {
				//std::cout << "JA\n";
				vsebina = nalozeniShaderi.at(c).koda;
			}
		}
		if (vsebina == "null") {
			std::ifstream in(imeDatoteke, std::ios::binary);
			if (in)
			{
				in.seekg(0, std::ios::end);
				vsebina.resize(in.tellg());
				in.seekg(0, std::ios::beg);
				in.read(&vsebina[0], vsebina.size());
				in.close();
				nalozeniShaderi.push_back({ imeDatoteke, vsebina });
			}
			else {
				std::cout << "napaka pri nalaganju sejdera\n";
			}
		}
		return(vsebina);
	}

	SHADER::SHADER() {
		//nic
	}

	void SHADER::kompajlajFragment(GLuint& fragmentShader, const char*& fragmentKoda, GLuint& ID) {
		glShaderSource(fragmentShader, 1, &fragmentKoda, NULL);
		glCompileShader(fragmentShader);

		GLint isCompiled1 = 0;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled1);
		if (isCompiled1 == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &errorLog[0]);

			glDeleteShader(fragmentShader);
			return;
		}
	}

	void SHADER::kompajlajVertex(GLuint& vertexShader, const char*& vertexKoda, GLuint& ID) {
		//glfwMakeContextCurrent();
		
		glShaderSource(vertexShader, 1, &vertexKoda, NULL);
		glCompileShader(vertexShader);
		//soNapake(vertexShader, "VERTEX");

		GLint isCompiled0 = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled0);
		if (isCompiled0 == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &errorLog[0]);

			glDeleteShader(vertexShader);
			return;
		}
	}

	SHADER::SHADER(const char* vertexShaderDatoteka, const char* fragmentShaderDatoteka)
	{
		STOPARCA st1;
		st1.Zacni();
		//nalozi kodo sharedov iz diska
		std::string vertexKodaStr = dobiVsebinoShadera(vertexShaderDatoteka);
		std::string fragmentKodaStr = dobiVsebinoShadera(fragmentShaderDatoteka);

		// pretvori string v const char* ker JA
		const char* vertexKoda = vertexKodaStr.c_str();
		const char* fragmentKoda = fragmentKodaStr.c_str();

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		kompajlajVertex(vertexShader, vertexKoda, ID);
		kompajlajFragment(fragmentShader, fragmentKoda, ID);

		ID = glCreateProgram();
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);
		soNapake(ID, "PROGRAM");

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		shaderLOG << st1.Koncaj();
		shaderLOG++;

	}

	SHADER::SHADER(const char* vertexShaderDatoteka, const char* fragmentShaderDatoteka, BARVA br)
	{
		STOPARCA st1;
		st1.Zacni();
		//nalozi kodo sharedov iz diska
		std::string vertexKodaStr = dobiVsebinoShadera(vertexShaderDatoteka);
		std::string fragmentKodaStr = dobiVsebinoShadera(fragmentShaderDatoteka);

		fragmentKodaStr.insert(fragmentKodaStr.find("vec4(") + 5,
			std::to_string(br.R) + ", " +
			std::to_string(br.G) + ", " +
			std::to_string(br.B) + ", " +
			std::to_string(br.alfa));

		// pretvori string v const char*
		const char* vertexKoda = vertexKodaStr.c_str();
		const char* fragmentKoda = fragmentKodaStr.c_str();

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		//std::future<void> t1 = std::async(std::launch::async , &SHADER::kompajlajVertex, this, std::ref(vertexShader), std::ref(vertexKoda), std::ref(ID));
		
		kompajlajVertex(vertexShader, vertexKoda, ID);
		kompajlajFragment(fragmentShader, fragmentKoda, ID);

		//t1.get();

		//std::thread t1(std::bind(&SHADER::kompajlajVertex, this, std::ref(vertexShader), std::ref(vertexKoda), std::ref(ID)));
		//std::thread t2(std::bind(&SHADER::kompajlajFragment, this, std::ref(fragmentShader), std::ref(fragmentKoda), std::ref(ID)));

		//t1.join();
		//t2.join();

		//soNapake(fragmentShader, "FRAGMENT");

		ID = glCreateProgram();

		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);
		soNapake(ID, "PROGRAM");
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		shaderLOG << st1.Koncaj();
		shaderLOG++;
	}

	// Aktivira shader
	void SHADER::Aktiviraj()
	{
		glUseProgram(ID);
	}

	// zbrise shader
	void SHADER::Zbrisi()
	{
		glDeleteProgram(ID);
	}

	// Preglej ce so napake
	void SHADER::soNapake(unsigned int shader, const char* tip)
	{
		GLint jeKompajlalo;

		//tu not sharanis napako
		char infoLog[1024];
		if (tip != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &jeKompajlalo);
			if (jeKompajlalo == GL_FALSE)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "SHADER_COMPILATION_ERROR for:" << tip << "\n" << infoLog << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &jeKompajlalo);
			if (jeKompajlalo == GL_FALSE)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "SHADER_LINKING_ERROR for:" << tip << "\n" << infoLog << std::endl;
			}
		}
	}
}