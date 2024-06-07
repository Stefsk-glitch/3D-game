#pragma once

class Shape {
	public:
		Shape();

		virtual int update(float deltaTim, unsigned char* color) { return 0; };
		virtual void draw() {};
};