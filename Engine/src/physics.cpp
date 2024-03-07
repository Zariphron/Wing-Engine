#include "physics.h"

GravitationalForce::GravitationalForce(const float &g) {
	gravity = g;
}

void GravitationalForce::setGravity(const float &g) {
	gravity = g;
}

float Conversions::AbsoluteTempurature(float initTemp, int format) {
	float kelvin = initTemp;
	switch (format)	{
	case 0:
		kelvin = (kelvin - 32) * 5 / 9 + 273.15;
		break;
	case 1:
		kelvin += 273.15;
		break;
	}
	return kelvin;
}

float Conversions::getCelcius(float kelvin) {
	return kelvin - 273.15;
}