#include "cube.h"
#include "tigl.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

using tigl::Vertex;

Cube::Cube() : position(0.0f, 0.0f, -10.0f), rotationAngleY(0.0f), rotationAngleX(0.0f) { }

void Cube::update(float deltaTime) {
    position.x += 20 * deltaTime;

    if (position.x > 350) { position.x = 0; }

    //rotationAngleX += 30.0f * deltaTime; // 30 degrees per second on x-axis
    //if (rotationAngleX > 360.0f)
    //    rotationAngleX -= 360.0f;
}

void Cube::draw() {
    const float scale = 5.0f;
    const glm::vec4 color(0, 0, 1, 1);

    glm::mat4 scaling = glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, scale));
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotation = rotationX * rotationY;

    glm::mat4 modelMatrix = translation * rotation * scaling;

    tigl::begin(GL_TRIANGLES);

    // Front face
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(-0.5f, -0.5f, 0.5f, 1), color));
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(0.5f, -0.5f, 0.5f, 1), color));
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(0.5f, 0.5f, 0.5f, 1), color));

    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(-0.5f, -0.5f, 0.5f, 1), color));
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(-0.5f, 0.5f, 0.5f, 1), color));
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(0.5f, 0.5f, 0.5f, 1), color));

    // Back face
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(-0.5f, -0.5f, -0.5f, 1), color));
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(0.5f, -0.5f, -0.5f, 1), color));
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(0.5f, 0.5f, -0.5f, 1), color));

    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(-0.5f, -0.5f, -0.5f, 1), color));
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(-0.5f, 0.5f, -0.5f, 1), color));
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(0.5f, 0.5f, -0.5f, 1), color));

    // Left face
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(-0.5f, -0.5f, -0.5f, 1), color));
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(-0.5f, -0.5f, 0.5f, 1), color));
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(-0.5f, 0.5f, 0.5f, 1), color));

    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(-0.5f, -0.5f, -0.5f, 1), color));
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(-0.5f, 0.5f, -0.5f, 1), color));
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(-0.5f, 0.5f, 0.5f, 1), color));

    // Right face
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(0.5f, -0.5f, -0.5f, 1), color));
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(0.5f, -0.5f, 0.5f, 1), color));
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(0.5f, 0.5f, 0.5f, 1), color));

    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(0.5f, -0.5f, -0.5f, 1), color));
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(0.5f, 0.5f, -0.5f, 1), color));
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(0.5f, 0.5f, 0.5f, 1), color));

    // Top face
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(-0.5f, 0.5f, -0.5f, 1), color));
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(0.5f, 0.5f, -0.5f, 1), color));
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(0.5f, 0.5f, 0.5f, 1), color));

    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(-0.5f, 0.5f, -0.5f, 1), color));
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(-0.5f, 0.5f, 0.5f, 1), color));
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(0.5f, 0.5f, 0.5f, 1), color));

    // Bottom face
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(-0.5f, -0.5f, -0.5f, 1), color));
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(0.5f, -0.5f, -0.5f, 1), color));
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(0.5f, -0.5f, 0.5f, 1), color));

    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(-0.5f, -0.5f, -0.5f, 1), color));
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(-0.5f, -0.5f, 0.5f, 1), color));
    tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(0.5f, -0.5f, 0.5f, 1), color));

    tigl::end();
}