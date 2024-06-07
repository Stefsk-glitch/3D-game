#include "cube.h"
#include "tigl.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

using tigl::Vertex;

Cube::Cube() : position(0.0f, 0.0f, -10.0f), rotationAngleY(0.0f), rotationAngleX(0.0f) { counter = 0; hit = false; }

int Cube::update(float deltaTime, unsigned char* color) {
    position.x += 20 * deltaTime;

    if (position.x > 350) { position.x = 0; }

    if (hit)
    {
        counter++;
        
        if (counter == 120)
        {
            hit = false;
            position.x = 0;
            rotationAngleY = 0;
            counter = 0;
        }
    }

    if ((int)color[2] > 150 || hit)
    {
        rotationAngleY += 90.0f * deltaTime; // 90 degrees per second on y-axis
        if (rotationAngleY > 360.0f)
            rotationAngleY -= 360.0f;

        if (!hit)
        {
            hit = true;
            color[0] = 0;
            color[1] = 0;
            color[2] = 0;
            return 2;
        }
    }

    return 0;
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