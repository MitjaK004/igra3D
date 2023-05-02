#pragma once
#include <string>
#include <fstream>

namespace igra {
	class LOG
	{
	private:
		std::string imeDatoteke;
		std::string vrednosti;
		void preveriVelikost();
	public:
		LOG();
		LOG(std::string ImeDatoteke);
		void Datoteka(std::string ImeDatoteke);
		void NoviFrame();
		void Pocisti();
		LOG& operator<<(std::string dodaj);
		LOG& operator<<(const char* dodaj);
		LOG& operator<<(int a);
		LOG& operator<<(float a);
		LOG& operator<<(double a);
		LOG& operator<<(short a);
		LOG& operator<<(long a);
		LOG& operator<<(bool a);
		LOG& operator<<(char a);
		void operator++(int a);
		void Koncaj();
		void Zapri();
		~LOG();
	};
}