#pragma once

#include "shape.h"

#include <glm/glm.hpp>

class Triangle : public Shape {
public:
	Triangle();

	glm::vec3 position;
	float rotationAngleX;
	float rotationAngleY;
	int counter;
	bool hit;

	virtual int update(float deltaTime, unsigned char* color) override;
	virtual void draw() override;
};