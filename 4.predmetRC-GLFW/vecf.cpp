#include "vecf.h"

namespace igra {
	vec4f::vec4f() {
		for (short i = 0; i < 4; i++) {
			vrednost[i] = 0.0f;
		}
	}
	vec4f::vec4f(float a, float b, float c, float d) {
		vrednost[0] = a;
		vrednost[1] = b;
		vrednost[2] = c;
		vrednost[3] = d;
	}
	float& vec4f::operator [] (short a) {
		if (a < 4 && a > -1) {
			return vrednost[a];
		}
	}
	void vec4f::getArr(float(&a)[4]) {
		for (short i = 0; i < 4; i++) {
			a[i] = vrednost[i];
		}
	}
	vec8f::vec8f() {
		for (short i = 0; i < 8; i++) {
			vrednost[i] = 0.0f;
		}
	}
	vec8f::vec8f(float a, float b, float c, float d, float e, float f, float g, float h) {
		vrednost[0] = a;
		vrednost[1] = b;
		vrednost[2] = c;
		vrednost[3] = d;
		vrednost[4] = e;
		vrednost[5] = f;
		vrednost[6] = g;
		vrednost[7] = h;
	}
	float& vec8f::operator [] (short a) {
		if (a < 8 && a > -1) {
			return vrednost[a];
		}
	}
	void vec8f::getArr(float(&a)[8]) {
		for (short i = 0; i < 8; i++) {
			a[i] = vrednost[i];
		}
	}
}