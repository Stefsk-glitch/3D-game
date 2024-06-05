#include "triangle.h"
#include <iostream>

Triangle::Triangle() { }

void Triangle::update() {
    std::cout << "Hello Triangle" << std::endl;
}

void Triangle::draw() {
    std::cout << "draw Triangle" << std::endl;
}