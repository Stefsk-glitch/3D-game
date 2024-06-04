#include "tigl.h"
#include "cam.h"
#include "objectModel.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;
cam* camera;
ObjModel* model;

void init();
void update(float deltaTime);
void draw();

int main(void)
{
	if (!glfwInit())
		throw "Could not initialize glwf";

	window = glfwCreateWindow(1280, 720, "Game", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		throw "Could not initialize glwf";
	}
	glfwMakeContextCurrent(window);

	tigl::init();
	init();

	float lastTime = (float)glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		float currentTime = (float)glfwGetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		update(deltaTime);
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void init()
{
	int value[10];
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, value);

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (key == GLFW_KEY_ESCAPE)
				glfwSetWindowShouldClose(window, true);
		});

	camera = new cam(window);
	model = new ObjModel("models/car/honda_jazz.obj");
}

void update(float deltaTime)
{
	camera->update(window, deltaTime);

	model->position.x += 5 * deltaTime;

	model->rotationAngle += 45.0f * deltaTime; // 45 degrees per second
	if (model->rotationAngle > 360.0f)
		model->rotationAngle -= 360.0f;
}

void draw()
{
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 1000.0f);

	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setViewMatrix(camera->getMatrix());
	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	tigl::shader->enableColor(true);
	tigl::shader->enableLighting(true);
	tigl::shader->enableColorMult(true);
	tigl::shader->setLightCount(1);
	tigl::shader->setLightAmbient(0, glm::vec3(0.2f, 0.2f, 0.2f));
	tigl::shader->setLightDiffuse(0, glm::vec3(1.0f, 1.0f, 1.0f));
	tigl::shader->setLightSpecular(0, glm::vec3(1.0f, 1.0f, 1.0f));
	tigl::shader->setLightPosition(0, glm::vec3(10, 10, 10));
	tigl::shader->setShinyness(100);
	tigl::shader->enableFog(false);

	glEnable(GL_DEPTH_TEST);

	model->draw();
}
