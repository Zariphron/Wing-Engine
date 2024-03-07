#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Object {
public:
	virtual bool inside(glm::vec3 p) {
		return false;
	}

	glm::vec3 position;
	float rot = 0.0;
	glm::vec3 scale = glm::vec3(1, 1, 1);
	glm::mat4 transform() {
		glm::mat4 Translation = glm::translate(glm::mat4(1.0), glm::vec3(position));
		glm::mat4 RotationZ = glm::rotate(glm::mat4(1.0), glm::radians(rot), glm::vec3(0, 0, 1));
		glm::mat4 RotationY = glm::rotate(glm::mat4(1.0), glm::radians(rot), glm::vec3(0, 1, 0));
		glm::mat4 RotationX = glm::rotate(glm::mat4(1.0), glm::radians(rot), glm::vec3(1, 0, 0));
		glm::mat4 Scale = glm::scale(glm::mat4(1.0), scale);
		return Translation * RotationX * RotationY * RotationZ * Scale;
	}

	float mass;
};

class PhysicalForce {
public:
	double DRY_AIR_MOL_MASS = 0.0289652;
	double WATER_VAPOR_MOL_MASS = 0.018016;
	double UNIVERSAL_GAS_CONSTANT = 8.31446;
	double DRY_AIR_GAS_CONSTANT = 287.0500676;

	float SEA_LEVEL_DENSITY = 1.225;	// By default uses Earth values. kg/m3
	float SEA_LEVEL_STANDARD_TEMPURATURE = 288.15;	// In Kelvin
	float SEA_LEVEL_STANDARD_PRESSURE = 101325;		// In Pascal
};

class GravitationalForce {
public:
	float gravity = -9.80665;	// By default use Earth gravity
	GravitationalForce(const float &gravity);
	void setGravity(const float &gravity);
};

class AeroForce {
public:
	void AtmospherePressure(double &altitude);
	void AirDensityCalc(double &humidity, float &tempurature, double &altitude);
	void LiftForce(double &airDensity, double velocity, double surfaceArea, double liftCoefficient);
	void DragForce(double &airDensity, double velocity, double surfaceArea, double dragCoefficient);

	double humidity;
	float tempurature;
	double altitude;
	double airDensity;
};

class Conversions {
	float Altitude(double altitude, int format);
	float Speed(double velocity, int format);
	double SurfaceArea(double surface, int format);
	float AbsoluteTempurature(float initTemp, int format);
	float getCelcius(float kelvin);		// Only used after getting the absolute tempurature
};