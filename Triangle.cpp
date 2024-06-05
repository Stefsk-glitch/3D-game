#include "triangle.h"
#include "tigl.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

using tigl::Vertex;

Triangle::Triangle() : position(0.0f, 0.0f, -10.0f), rotationAngleY(0.0f), rotationAngleX(0.0f) { }

void Triangle::update(float deltaTime) {
    position.x -= 10 * deltaTime;

    std::cout << position.x;

    if (position.x < -400) { position.x = 0; }

    //rotationAngleX += 30.0f * deltaTime; // 30 degrees per second on x-axis
    //if (rotationAngleX > 360.0f)
    //    rotationAngleX -= 360.0f;
}

void Triangle::draw() {
    const float scale = 5.0f;
    const float height = 1.0f;
    const glm::vec4 color(0, 1, 0, 1);

    glm::mat4 scaling = glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, scale));
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotation = rotationX * rotationY;

    glm::mat4 modelMatrix = translation * rotation * scaling;

    tigl::begin(GL_TRIANGLES);

    // Base vertices
    glm::vec4 v0 = modelMatrix * glm::vec4(-0.5f, 0.0f, -0.5f, 1);
    glm::vec4 v1 = modelMatrix * glm::vec4(0.5f, 0.0f, -0.5f, 1);
    glm::vec4 v2 = modelMatrix * glm::vec4(0.5f, 0.0f, 0.5f, 1);
    glm::vec4 v3 = modelMatrix * glm::vec4(-0.5f, 0.0f, 0.5f, 1);

    // Highest point of the pyramid
    glm::vec4 apex = modelMatrix * glm::vec4(0.0f, height, 0.0f, 1);

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
