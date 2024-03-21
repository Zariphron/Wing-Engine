#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <map>

class Object {
public:
	virtual bool inside(glm::vec3 p) {
		return false;
	}

	glm::vec3 position;
	float rot = 0.0;
	glm::vec3 forces;
	glm::vec3 scale = glm::vec3(1, 1, 1);
	glm::mat4 transform() {
		glm::mat4 Translation = glm::translate(glm::mat4(1.0), glm::vec3(position));
		glm::mat4 RotationZ = glm::rotate(glm::mat4(1.0), glm::radians(rot), glm::vec3(0, 0, 1));
		glm::mat4 RotationY = glm::rotate(glm::mat4(1.0), glm::radians(rot), glm::vec3(0, 1, 0));
		glm::mat4 RotationX = glm::rotate(glm::mat4(1.0), glm::radians(rot), glm::vec3(1, 0, 0));
		glm::mat4 Scale = glm::scale(glm::mat4(1.0), scale);
		return Translation * RotationX * RotationY * RotationZ * Scale;
	}
	void draw();
	void update();
	void forceIntegrate();

	float mass;

};
// Consider using a singleton for the sake of memory management, useful if you want to maintain current state or keep track of thread pool
class Conversions {
	// Implement singleton for this class as the conversions will not change
	float Altitude(double altitude, int format);
	glm::vec3 Speed(glm::vec3 velocity, int format);
	double SurfaceArea(double surface, int format);
	float AbsoluteTempurature(float initTemp, int format);
	float getCelcius(float kelvin);		// Only used after getting the absolute tempurature
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

	glm::vec3 force;
	virtual void updateForce(Object *) = 0;
};

class GravitationalForce : public PhysicalForce {
	glm::vec3 gravity = glm::vec3(0, -9.80665, 0);	// By default use Earth gravity
public:
	GravitationalForce(const glm::vec3 &gravity);
	void updateForce(Object *);
	void setGravity(const glm::vec3 &gravity);
	float getGravity();
};

class AeroForce : public PhysicalForce {
public:
	void AtmospherePressure(double &altitude);
	void AirDensityCalc(double &humidity, float &tempurature, double &altitude);
	void ThrustForce(glm::vec3 velocity);
	void LiftForce(double &airDensity, glm::vec3 velocity, double surfaceArea, double liftCoefficient);
	void DragForce(double &airDensity, glm::vec3 velocity, double surfaceArea, double dragCoefficient);
	void updateForce(Object *);

	GravitationalForce &grav;
	Conversions &converter;
	glm::vec3 liftForce, dragForce;
	std::map<float, bool> dragCoef;
	float dragCoeffs[7] = {	// Optimal coefficients for flight are under 0.06
		0.47f,	// Spherical shape
		0.42f,	// Half-sphere shape
		0.38f,	// Half-sphere open side facing away from force
		0.5f,	// Cone shape, pointed side towards resistance
		1.05f,	// Cube shape, flat side forward
		0.04f,	// Streamlined body, like wings on aircraft
		0.09f	// Streamlined half-body
	};
	double reynoldsNumber;
	double humidity, pressure;
	float tempurature;
	double altitude, airDensity;
};