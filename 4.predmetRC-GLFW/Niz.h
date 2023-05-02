#pragma once
#include <string>
#include <vector>
using std::string;
using std::size_t;
using std::vector;

#define NIZ_ERR -999.9999f
#define NIZ_SUCCESS 1.0f

class Niz
{
private:
	string podatki = "NULL";
	char med_vrednostmi = ',';
	char med_vrsticami = ';';
public:
	Niz();
	Niz(string a);
	operator string();
	operator const char* ();
	vector<float> operator << (string a);
	void operator = (string a);
	void locilo_med_vrednostmi(char a);
	void locilo_med_vrsticami(char a);
};

typedef vector<float> VEC_F;
