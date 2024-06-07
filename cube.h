#pragma once

#include "shape.h"

#include <glm/glm.hpp>

class Cube : public Shape {
public:
	Cube();

	glm::vec3 position;
	float rotationAngleX;
	float rotationAngleY;
	int counter;
	bool hit;

	virtual int update(float deltaTime, unsigned char* color) override;
	virtual void draw() override;
};