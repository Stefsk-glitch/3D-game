#pragma once

#include "shape.h"

class Triangle : public Shape {
public:
	Triangle();

	virtual void update() override;
};