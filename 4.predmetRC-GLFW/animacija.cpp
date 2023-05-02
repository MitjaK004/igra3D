#include <iostream>
#include "animacija.h"
#include "oblike.h"

namespace igra {
	KEY_FRAME::KEY_FRAME() {
		vert[0] = 0.0f;
		vert[1] = 0.0f;
		vert[2] = 0.0f;
		vert[3] = 1.0f;
		vert[4] = 1.0f;
		vert[5] = 1.0f;
		vert[6] = 1.0f;
		vert[7] = 0.0f;
	}
	KEY_FRAME::KEY_FRAME(vec8f a) {
		vert[0] = a[0];
		vert[1] = a[1];
		vert[2] = a[2];
		vert[3] = a[3];
		vert[4] = a[4];
		vert[5] = a[5];
		vert[6] = a[6];
		vert[7] = a[7];
	}
	KEY_FRAME::KEY_FRAME(vec4f a) {
		vert[0] = 0.0f;
		vert[1] = 0.0f;
		vert[2] = 0.0f;
		vert[3] = 1.0f;
		vert[4] = 1.0f;
		vert[5] = 1.0f;
		vert[6] = 1.0f;
		vert[7] = 0.0f;

		vert[0] = a[0];
		vert[2] = a[1];
		vert[4] = a[2];
		vert[6] = a[3];
	}
	vec8f KEY_FRAME::getVec() {
		return vert;
	}
	void KEY_FRAME::operator << (vec4f a) {
		vert[0] = a[0];
		vert[2] = a[1];
		vert[4] = a[2];
		vert[6] = a[3];
	}
	void KEY_FRAME::operator << (vec8f a) {
		vert[0] = a[0];
		vert[1] = a[1];
		vert[2] = a[2];
		vert[3] = a[3];
		vert[4] = a[4];
		vert[5] = a[5];
		vert[6] = a[6];
		vert[7] = a[7];
	}

	void premakniEnFrame(vec4f& a, short steviloFramov, float trajanje) {
		float razlika = trajanje / (float)steviloFramov;
		a[0] += razlika;
		a[1] += razlika;
		a[2] += razlika;
		a[3] += razlika;
	}

	vec8f ANIMACIJA::getVec() {
		return trenutniKF;
	}
	void ANIMACIJA::operator() () {
		if (!anim) {
			stoparca.Zacni();
			anim = true;
		}
		float frame = trajanje / (float)key_frames.size();
		for (int c = 0; c < key_frames.size(); c++) {
			if (stoparca.Cas() > (frame - frame) && stoparca.Cas() <= frame) {
				trenutniKF = key_frames.at(c).getVec();
				oblika->vertecijiSlike(trenutniKF);
				break;
			}
			frame += frame;
		}
		if (anim && stoparca.Cas() > trajanje) {
			stoparca.Koncaj();
			anim = false;
		}
		return;
	}
	STOPARCA& ANIMACIJA::dobiStoparco() {
		return stoparca;
	}
	bool ANIMACIJA::Animiram() {
		return anim;
	}
	void ANIMACIJA::operator<<(OBLIKA* obl) {
		oblika = obl;
	}
	void ANIMACIJA::operator += (KEY_FRAME kf) {
		key_frames.push_back(kf);
	}
	void ANIMACIJA::Trajanje(float t) {
		trajanje = t;
	}
	KEY_FRAME& ANIMACIJA::operator[] (int a) {
		return key_frames.at(a);
	}
	void ANIMACIJA::narediKF() {
		key_frames.push_back(KEY_FRAME());
	}
	void ANIMACIJA::operator++ () {
		key_frames.push_back(KEY_FRAME());
	}
}