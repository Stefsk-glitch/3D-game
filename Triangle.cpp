#include "triangle.h"
#include "tigl.h"
#include <iostream>

using tigl::Vertex;

Triangle::Triangle() { }

void Triangle::update() {
    std::cout << "Hello Triangle" << std::endl;
}

void Triangle::draw() {
    const float scale = 5.0f; 
    const float height = 5.0f;
    const glm::vec4 color(0, 1, 0, 1);

    tigl::begin(GL_TRIANGLES);

    // Base vertices
    glm::vec4 v0 = glm::vec4(-0.5f * scale, 0.0f, -0.5f * scale, 1);
    glm::vec4 v1 = glm::vec4(0.5f * scale, 0.0f, -0.5f * scale, 1);
    glm::vec4 v2 = glm::vec4(0.5f * scale, 0.0f, 0.5f * scale, 1);
    glm::vec4 v3 = glm::vec4(-0.5f * scale, 0.0f, 0.5f * scale, 1);

    // Highest point of the pyramid
    glm::vec4 apex = glm::vec4(0.0f, height, 0.0f, 1);

    // Side faces
    tigl::addVertex(Vertex::PC(v0, color));
    tigl::addVertex(Vertex::PC(v1, color));
    tigl::addVertex(Vertex::PC(apex, color));

    tigl::addVertex(Vertex::PC(v1, color));
    tigl::addVertex(Vertex::PC(v2, color));
    tigl::addVertex(Vertex::PC(apex, color));

    tigl::addVertex(Vertex::PC(v2, color));
    tigl::addVertex(Vertex::PC(v3, color));
    tigl::addVertex(Vertex::PC(apex, color));

    tigl::addVertex(Vertex::PC(v3, color));
    tigl::addVertex(Vertex::PC(v0, color));
    tigl::addVertex(Vertex::PC(apex, color));

    // Bottom square
    tigl::addVertex(Vertex::PC(v0, color));
    tigl::addVertex(Vertex::PC(v1, color));
    tigl::addVertex(Vertex::PC(v2, color));

    tigl::addVertex(Vertex::PC(v2, color));
    tigl::addVertex(Vertex::PC(v3, color));
    tigl::addVertex(Vertex::PC(v0, color));

    tigl::end();
}