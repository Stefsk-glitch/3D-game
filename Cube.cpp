#include "cube.h"
#include "tigl.h"
#include <iostream>

using tigl::Vertex;

Cube::Cube() { }

void Cube::update() {
    std::cout << "Hello Cube" << std::endl;
}

void Cube::draw() {
    const float scale = 5.0f;
    const glm::vec4 color(0, 1, 0, 1);

    tigl::begin(GL_TRIANGLES);

    // Front face
    tigl::addVertex(Vertex::PC(glm::vec4(-0.5f * scale, -0.5f * scale, 0.5f * scale, 1), color));
    tigl::addVertex(Vertex::PC(glm::vec4(0.5f * scale, -0.5f * scale, 0.5f * scale, 1), color));
    tigl::addVertex(Vertex::PC(glm::vec4(0.5f * scale, 0.5f * scale, 0.5f * scale, 1), color));

    tigl::addVertex(Vertex::PC(glm::vec4(-0.5f * scale, -0.5f * scale, 0.5f * scale, 1), color));
    tigl::addVertex(Vertex::PC(glm::vec4(-0.5f * scale, 0.5f * scale, 0.5f * scale, 1), color));
    tigl::addVertex(Vertex::PC(glm::vec4(0.5f * scale, 0.5f * scale, 0.5f * scale, 1), color));

    // Back face
    tigl::addVertex(Vertex::PC(glm::vec4(-0.5f * scale, -0.5f * scale, -0.5f * scale, 1), color));
    tigl::addVertex(Vertex::PC(glm::vec4(0.5f * scale, -0.5f * scale, -0.5f * scale, 1), color));
    tigl::addVertex(Vertex::PC(glm::vec4(0.5f * scale, 0.5f * scale, -0.5f * scale, 1), color));

    tigl::addVertex(Vertex::PC(glm::vec4(-0.5f * scale, -0.5f * scale, -0.5f * scale, 1), color));
    tigl::addVertex(Vertex::PC(glm::vec4(-0.5f * scale, 0.5f * scale, -0.5f * scale, 1), color));
    tigl::addVertex(Vertex::PC(glm::vec4(0.5f * scale, 0.5f * scale, -0.5f * scale, 1), color));

    // Left face
    tigl::addVertex(Vertex::PC(glm::vec4(-0.5f * scale, -0.5f * scale, -0.5f * scale, 1), color));
    tigl::addVertex(Vertex::PC(glm::vec4(-0.5f * scale, -0.5f * scale, 0.5f * scale, 1), color));
    tigl::addVertex(Vertex::PC(glm::vec4(-0.5f * scale, 0.5f * scale, 0.5f * scale, 1), color));

    tigl::addVertex(Vertex::PC(glm::vec4(-0.5f * scale, -0.5f * scale, -0.5f * scale, 1), color));
    tigl::addVertex(Vertex::PC(glm::vec4(-0.5f * scale, 0.5f * scale, -0.5f * scale, 1), color));
    tigl::addVertex(Vertex::PC(glm::vec4(-0.5f * scale, 0.5f * scale, 0.5f * scale, 1), color));

    // Right face
    tigl::addVertex(Vertex::PC(glm::vec4(0.5f * scale, -0.5f * scale, -0.5f * scale, 1), color));
    tigl::addVertex(Vertex::PC(glm::vec4(0.5f * scale, -0.5f * scale, 0.5f * scale, 1), color));
    tigl::addVertex(Vertex::PC(glm::vec4(0.5f * scale, 0.5f * scale, 0.5f * scale, 1), color));

    tigl::addVertex(Vertex::PC(glm::vec4(0.5f * scale, -0.5f * scale, -0.5f * scale, 1), color));
    tigl::addVertex(Vertex::PC(glm::vec4(0.5f * scale, 0.5f * scale, -0.5f * scale, 1), color));
    tigl::addVertex(Vertex::PC(glm::vec4(0.5f * scale, 0.5f * scale, 0.5f * scale, 1), color));

    // Top face
    tigl::addVertex(Vertex::PC(glm::vec4(-0.5f * scale, 0.5f * scale, -0.5f * scale, 1), color));
    tigl::addVertex(Vertex::PC(glm::vec4(0.5f * scale, 0.5f * scale, -0.5f * scale, 1), color));
    tigl::addVertex(Vertex::PC(glm::vec4(0.5f * scale, 0.5f * scale, 0.5f * scale, 1), color));

    tigl::addVertex(Vertex::PC(glm::vec4(-0.5f * scale, 0.5f * scale, -0.5f * scale, 1), color));
    tigl::addVertex(Vertex::PC(glm::vec4(-0.5f * scale, 0.5f * scale, 0.5f * scale, 1), color));
    tigl::addVertex(Vertex::PC(glm::vec4(0.5f * scale, 0.5f * scale, 0.5f * scale, 1), color));

    // Bottom face
    tigl::addVertex(Vertex::PC(glm::vec4(-0.5f * scale, -0.5f * scale, -0.5f * scale, 1), color));
    tigl::addVertex(Vertex::PC(glm::vec4(0.5f * scale, -0.5f * scale, -0.5f * scale, 1), color));
    tigl::addVertex(Vertex::PC(glm::vec4(0.5f * scale, -0.5f * scale, 0.5f * scale, 1), color));

    tigl::addVertex(Vertex::PC(glm::vec4(-0.5f * scale, -0.5f * scale, -0.5f * scale, 1), color));
    tigl::addVertex(Vertex::PC(glm::vec4(-0.5f * scale, -0.5f * scale, 0.5f * scale, 1), color));
    tigl::addVertex(Vertex::PC(glm::vec4(0.5f * scale, -0.5f * scale, 0.5f * scale, 1), color));

    tigl::end();
}