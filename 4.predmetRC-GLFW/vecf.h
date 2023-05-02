#pragma once

namespace igra {
	class vec4f {
	private:
		float vrednost[4];
	public:
		vec4f();
		vec4f(float a, float b, float c, float d);
		void getArr(float(&a)[4]);
		float& operator [] (short a);
	};
	class vec8f {
	private:
		float vrednost[8];
	public:
		vec8f();
		vec8f(float a, float b, float c, float d, float e, float f, float g, float h);
		void getArr(float(&a)[8]);
		float& operator [] (short a);
	};
}