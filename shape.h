#pragma once

class Shape {
	public:
		Shape();

		virtual void update(float deltaTime) {};
		virtual void draw() {};
};