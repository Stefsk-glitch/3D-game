#include "cam.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

cam::cam(GLFWwindow* window)
{
	position = glm::vec3(0.0f, -20.0f, 10.0f);
	rotation = glm::vec2(0, 0);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

glm::mat4 cam::getMatrix()
{
	glm::mat4 ret(1.0f);

	ret = glm::rotate(ret, rotation.x, glm::vec3(1, 0, 0));
	ret = glm::rotate(ret, rotation.y, glm::vec3(0, 1, 0));
	ret = glm::translate(ret, position);

	return ret;
}

void cam::move(float angle, float fac, float deltaTime) {
	float velocity = fac * deltaTime;

	position.x += (float)cos(rotation.y + glm::radians(angle)) * velocity;
	position.z += (float)sin(rotation.y + glm::radians(angle)) * velocity;
}

void cam::update(GLFWwindow* window, float deltaTime)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	static double lastX = x;
	static double lastY = y;

	rotation.x -= (float)(lastY - y) / 750.0f;
	rotation.y -= (float)(lastX - x) / 750.0f;

	lastX = x;
	lastY = y;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		move(0, 5.0f, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		move(180, 5.0f, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		move(90, 5.0f, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		move(-90, 5.0f, deltaTime);
}