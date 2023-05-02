#pragma once
#include <chrono>
#include <iostream>
#include <vector>
#include <functional>

namespace igra {
	extern std::vector<int> c_id;

	typedef std::function<void()> KLIC;

	class STOPARCA {
	private:
		std::chrono::system_clock::time_point zacetek = std::chrono::system_clock::now();
		float ret = 0;
		int id = 0;
		bool vrniPovprecje = false;
		std::vector<float> retVr;
	public:
		STOPARCA(bool VP = false);
		~STOPARCA();
		void Zacni();
		float Koncaj();
		float Resetiraj();
		float Cas();
		float PrejsnjiCas();
		std::vector<float> PrejsnjiCasi();
		float Povprecje();
		void Odstevaj(int cas, KLIC k);
	};
}