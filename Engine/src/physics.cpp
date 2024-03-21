#include "physics.h"

GravitationalForce::GravitationalForce(const glm::vec3 &g) {
	gravity = g;
}

void GravitationalForce::updateForce(Object * object) {
	object->forces += gravity * object->mass;
}

void GravitationalForce::setGravity(const glm::vec3 &g) {
	gravity = g;
}

float GravitationalForce::getGravity() {
	return gravity.y;
}

void AeroForce::AtmospherePressure(double& altitude) {
	double tempLapseRate = 0.0065;
	pressure = static_cast<double>(SEA_LEVEL_STANDARD_PRESSURE) * pow((1 - ((tempLapseRate * altitude)
		/ SEA_LEVEL_STANDARD_TEMPURATURE)), ((grav.getGravity() * DRY_AIR_MOL_MASS) / (UNIVERSAL_GAS_CONSTANT * tempLapseRate)));
}

void AeroForce::AirDensityCalc(double &humidity, float &tempurature, double &altitude) {
	AtmospherePressure(altitude);
	if (humidity > 0) {
		float cel;	// Use converter
		double saturation = 6.1079 * pow(10, ((7.5 * cel) / tempurature));
		double vPres = humidity * saturation;
		double dPres = pressure - vPres;

		airDensity = (dPres * DRY_AIR_MOL_MASS + vPres * WATER_VAPOR_MOL_MASS) / (UNIVERSAL_GAS_CONSTANT * tempurature);
	}
	else {
		airDensity = pressure / (DRY_AIR_GAS_CONSTANT * tempurature);
	}
}

void AeroForce::ThrustForce(glm::vec3 velocity) {
	force += velocity; /*Needs delta mass over delta time*/
}

void AeroForce::LiftForce(double &airDensity, glm::vec3 velocity, double surfaceArea, double liftCoefficient) {
	/* Higher lift coefficients are better for flight */
	dragForce.x = liftCoefficient * (airDensity * glm::pow(velocity.x, 2) / 2) * surfaceArea;
	dragForce.y = liftCoefficient * (airDensity * glm::pow(velocity.y, 2) / 2) * surfaceArea;
	dragForce.z = liftCoefficient * (airDensity * glm::pow(velocity.z, 2) / 2) * surfaceArea;
}

void AeroForce::DragForce(double &airDensity, glm::vec3 velocity, double surfaceArea, double dragCoefficient) {
	/*Object shape will grant a specific drag coefficient, numbers lower than 0.06 are ideal for flight.
	Velocity should be relative to object motion */
	dragForce.x = airDensity * (glm::pow(velocity.x, 2) / 2) * surfaceArea * dragCoefficient;
	dragForce.y = airDensity * (glm::pow(velocity.y, 2) / 2) * surfaceArea * dragCoefficient;
	dragForce.z = airDensity * (glm::pow(velocity.z, 2) / 2) * surfaceArea * dragCoefficient;
}

void AeroForce::updateForce(Object * object) {

}

float Conversions::Altitude(double alt, int format) {
	switch (format) { // Converts measurements to meters for convenience
	case 0:		// Inches
		return alt / 39.3700787;
	case 1:		// Feet
		return alt / 3.28084;
	case 2:		// Yards
		return alt / 1.093613;
	case 3:		// Miles
		return alt * 1609.344;
	case 4:		// Meters
		return alt;
	case 5:		// Kilometers
		return alt * 1000;
	}
}

glm::vec3 Conversions::Speed(glm::vec3 v, int format) {
	glm::vec3 velocity = v;
	switch (format) {	// Converts speed to m/s for convenience
	case 0:		// f/s
		velocity.x = v.x * 0.3048;
		velocity.y = v.y * 0.3048;
		velocity.z = v.z * 0.3048;
		return velocity;
	case 1:		// MpH
		velocity.x = v.x * 0.44704;
		velocity.y = v.y * 0.44704;
		velocity.z = v.z * 0.44704;
		return velocity;
	case 2:		// m/s
		return velocity;
	case 3:		// KpH
		velocity.x = v.x * 0.277778;
		velocity.y = v.y * 0.277778;
		velocity.z = v.z * 0.277778;
		return velocity;
	}
}

double Conversions::SurfaceArea(double surface, int format) {

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