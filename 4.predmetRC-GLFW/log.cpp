#include <string>
#include <fstream>
#include "log.h"

namespace igra {
	void LOG::preveriVelikost() {
		if (vrednosti.size() > 10000000) {
			std::string chacheVR = vrednosti;
			vrednosti.clear();
			vrednosti = chacheVR.substr(9000000, chacheVR.size() - 1);
		}
	}

	LOG::LOG() {
		imeDatoteke = "defolt";
	}

	LOG::LOG(std::string ImeDatoteke) {
		imeDatoteke = ImeDatoteke;
	}

	void LOG::Datoteka(std::string ImeDatoteke) {
		imeDatoteke = ImeDatoteke;
	}

	void LOG::NoviFrame() {
		vrednosti += "\n\n\n";
		vrednosti += "----------------------------------------------------------------";
		vrednosti += "\n\n\n";
	}

	void LOG::Pocisti() {
		vrednosti.clear();
	}

	LOG& LOG::operator<< (std::string dodaj) {
		preveriVelikost();
		vrednosti += dodaj;
		return *this;
	}

	LOG& LOG::operator<< (const char* dodaj) {
		preveriVelikost();
		vrednosti.append(dodaj);
		return *this;
	}

	LOG& LOG::operator<<(int a) {
		preveriVelikost();
		vrednosti += std::to_string(a);
		return *this;
	}

	LOG& LOG::operator<<(float a) {
		preveriVelikost();
		vrednosti += std::to_string(a);
		return *this;
	}

	LOG& LOG::operator<<(double a) {
		preveriVelikost();
		vrednosti += std::to_string(a);
		return *this;
	}

	LOG& LOG::operator<<(short a) {
		preveriVelikost();
		vrednosti += std::to_string(a);
		return *this;
	}

	LOG& LOG::operator<<(long a) {
		preveriVelikost();
		vrednosti += std::to_string(a);
		return *this;
	}

	LOG& LOG::operator<<(bool a) {
		preveriVelikost();
		vrednosti += std::to_string(a);
		return *this;
	}

	LOG& LOG::operator<<(char a) {
		preveriVelikost();
		vrednosti += std::to_string(a);
		return *this;
	}

	void LOG::operator++ (int a) {
		preveriVelikost();
		vrednosti += "\n";
	}

	LOG::~LOG() {
		std::ofstream izhod((imeDatoteke + ".log").c_str());
		if (izhod.is_open()) {
			izhod << vrednosti;
		}
		izhod.close();
	}

	void LOG::Zapri() {
		std::ofstream izhod((imeDatoteke + ".log").c_str());
		if (izhod.is_open()) {
			izhod << vrednosti;
		}
		izhod.close();
		delete this;
	}

	void LOG::Koncaj() {
		std::ofstream izhod((imeDatoteke + ".log").c_str());
		if (izhod.is_open()) {
			izhod << vrednosti;
		}
		izhod.close();
	}
}