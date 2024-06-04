#pragma once
#include <glm/glm.hpp>

struct GLFWwindow;

class cam
{
public:
	cam(GLFWwindow*);

	glm::mat4 getMatrix();
	void update(GLFWwindow* window, float deltaTime);

private:
	glm::vec3 position;
	glm::vec2 rotation;

	void move(float angle, float fac, float deltaTime);
};
