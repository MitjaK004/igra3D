#pragma once
#include <functional>
#include "cas.h"
#include "oblike.h"
#include <vector>
#include "vecf.h"
#define ANIM_ERR vec8f(0,0,0,0,0,0,0,0)

namespace igra {
	struct KEY_FRAME {
		vec8f vert;
		KEY_FRAME();
		KEY_FRAME(vec8f a);
		KEY_FRAME(vec4f a);
		vec8f getVec();
		void operator << (vec4f a);
		void operator << (vec8f a);
	};

	extern void premakniEnFrame(vec4f& a, short steviloFramov, float trajanje);

	class ANIMACIJA
	{
	private:
		OBLIKA* oblika;
		float trajanje = 1000.0f;
		vec8f trenutniKF;
		std::vector<KEY_FRAME> key_frames;
		STOPARCA stoparca;
		bool anim = false;
	public:
		void operator() ();
		bool Animiram();
		STOPARCA& dobiStoparco();
		vec8f getVec();
		KEY_FRAME& operator[] (int a);
		void operator << (OBLIKA* obl);
		void operator += (KEY_FRAME kf);
		void operator++ ();
		void narediKF();
		void Trajanje(float t);
	};
}

