#pragma once

#include "shape.h"

#include <glm/glm.hpp>

class Cube : public Shape {
public:
	Cube();

	glm::vec3 position;
	float rotationAngleX;
	float rotationAngleY;

	virtual void update(float deltaTime) override;
	virtual void draw() override;
};