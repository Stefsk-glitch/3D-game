#pragma once

#include "shape.h"

#include <glm/glm.hpp>

class Triangle : public Shape {
public:
	Triangle();

	glm::vec3 position;
	float rotationAngleX;
	float rotationAngleY;

	virtual void update(float deltaTime) override;
	virtual void draw() override;
};