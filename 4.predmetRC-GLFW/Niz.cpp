#include "Niz.h"
#include <string>
#include <vector>
#include <stdlib.h>
using std::vector;
using std::string;
using std::size_t;
using std::stof;

Niz::Niz() {
	podatki = "NULL";
}

Niz::Niz(string a) {
	podatki = a;
}

Niz::operator const char* () {
	return podatki.c_str();
}

Niz::operator std::string() {
	return podatki;
}

void Niz::operator = (string a) {
	podatki = a;
}

void Niz::locilo_med_vrednostmi(char a) {
	med_vrednostmi = a;
}

void Niz::locilo_med_vrsticami(char a) {
	med_vrsticami = a;
}

vector<float> Niz::operator<<(string a) {
	size_t pozicija = podatki.find(a);
	vector<float> tempf;
	if (pozicija != string::npos) {
		pozicija += a.length();
		vector<string> temps;
		for (int c = pozicija; c < podatki.length(); c++) {
			if (podatki.at(c) == med_vrednostmi) {
				temps.push_back("");
			}
			else if (podatki.at(c) == med_vrsticami) {
				break;
			}
			else {
				if (temps.size() == 0) {
					temps.push_back("");
				}
				temps.at(temps.size() - 1) += podatki.at(c);
			}
		}
		for (auto temp : temps) {
			tempf.push_back(stof(temp));
		}
	}
	else {
		tempf.push_back(NIZ_ERR);
	}
	return tempf;
}