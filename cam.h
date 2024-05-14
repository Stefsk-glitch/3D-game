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
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec2 rotation = glm::vec2(0, 0);

	void move(float angle, float fac, float deltaTime);
};
