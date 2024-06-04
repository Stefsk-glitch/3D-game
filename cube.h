#pragma once

#include "shape.h"

class Cube : public Shape {
public:
	Cube();

	virtual void update() override;
};