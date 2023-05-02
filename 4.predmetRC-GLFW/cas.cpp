#include "cas.h"
#include <chrono>
#include <iostream>
#include <vector>
#include <functional>
#include <thread>
#include <Windows.h>

namespace igra {
	std::vector<int> c_id;

	STOPARCA::STOPARCA(bool VP) {
		if (VP == true) {
			vrniPovprecje = true;
			c_id.push_back(0);
			id = c_id.size();
		}
	}
	STOPARCA::~STOPARCA() {
		if (vrniPovprecje == true) {
			std::cout << "\n------------------\nID:  " << id << "\n"
				<< Povprecje() << "\n------------------\n";
		}
	}
	void STOPARCA::Zacni() {
		zacetek = std::chrono::system_clock::now();
	}
	float STOPARCA::Koncaj() {
		std::chrono::system_clock::time_point konec = std::chrono::system_clock::now();
		std::chrono::duration<float> prC = konec - zacetek;
		ret = prC.count() * 1000.0f;
		retVr.push_back(prC.count() * 1000.0f);
		return ret;
	}
	float STOPARCA::Resetiraj() {
		std::chrono::system_clock::time_point konec = std::chrono::system_clock::now();
		std::chrono::duration<float> prC = konec - zacetek;
		ret = prC.count() * 1000.0f;
		retVr.push_back(prC.count() * 1000.0f);
		zacetek = std::chrono::system_clock::now();
		return ret;
	}
	float STOPARCA::Cas() {
		std::chrono::system_clock::time_point konec = std::chrono::system_clock::now();
		std::chrono::duration<float> prC = konec - zacetek;
		float rret = prC.count() * 1000.0f;
		return rret;
	}
	float STOPARCA::PrejsnjiCas() {
		return ret;
	}
	std::vector<float> STOPARCA::PrejsnjiCasi() {
		return retVr;
	}
	float STOPARCA::Povprecje() {
		float povprecje = 0.0f;
		for (int c = 0; c < retVr.size(); c++) {
			povprecje += retVr.at(c);
		}
		povprecje /= retVr.size();
		return povprecje;
	}
	void STOPARCA::Odstevaj(int cas_v_ms, KLIC k) {
		KLIC cakaj = [&] {
			Sleep(cas_v_ms);
			k();
		};
		std::thread{ cakaj }.detach();
	}
}