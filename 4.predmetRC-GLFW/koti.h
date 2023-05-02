#pragma once
#define PI 3.14159265359
double preveriKot(double kot) {
	if (kot < 0) {
		kot += PI;
	}
	else if(kot > 2*PI) {
		kot -= PI;
	}
	return kot;
}