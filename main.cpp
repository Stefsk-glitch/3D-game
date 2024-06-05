#include "tigl.h"
#include "cam.h"
#include "cube.h"
#include "triangle.h"
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

std::list<Shape*> shapes;

unsigned char* clickedPixel = new unsigned char[3]();
int score = 0;

void init();
void update(float deltaTime);
void draw();
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

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

	glfwSetMouseButtonCallback(window, mouse_button_callback);

	camera = new cam(window);
	
	model = new ObjModel("models/target/10480_Archery_target_v1_max2011_iteration-2.obj");
	shapes.push_back(model);
	shapes.push_back(new Cube());
	shapes.push_back(new Triangle());
}

void update(float deltaTime)
{
	camera->update(window, deltaTime);

	if ((int)clickedPixel[0] != 0 || (int)clickedPixel[1] != 0 || (int)clickedPixel[2] != 0)
	{
		std::cout << (int)clickedPixel[0] << " R" << std::endl;
		std::cout << (int)clickedPixel[1] << " G" << std::endl;
		std::cout << (int)clickedPixel[2] << " B" << std::endl;
		std::cout << "--------------------------------" << std::endl;
	}

	for (auto &shape : shapes) {
		shape->update(deltaTime);
	}

	clickedPixel[0] = 0;
	clickedPixel[1] = 0;
	clickedPixel[2] = 0;
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
	tigl::shader->setLightPosition(0, glm::vec3(25, 25, 25));
	tigl::shader->setShinyness(100);
	tigl::shader->enableFog(false);

	glEnable(GL_DEPTH_TEST);

	for (auto& shape : shapes) {
		shape->draw();
	}

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 20.0f, -10.0f));

	const glm::vec4 purple(0, 1, 1, 1);
	const glm::vec4 cyan(1, 0, 1, 1);

	tigl::begin(GL_TRIANGLES);

	// Drawing the square
	tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(-10, -1, -10, 1), purple));
	tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(-10, -1, 10, 1), purple));
	tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(10, -1, 10, 1), purple));

	tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(-10, -1, -10, 1), purple));
	tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(10, -1, -10, 1), purple));
	tigl::addVertex(Vertex::PC(modelMatrix * glm::vec4(10, -1, 10, 1), purple));

	// Drawing the circle
	const float pixelOffset = 0.01f; 
	glm::vec4 center = modelMatrix * glm::vec4(0, -1 + pixelOffset, 0, 1);
	const float radius = 5.0f; 
	const int numVertices = 20; 

	for (int i = 0; i < numVertices; ++i) {
		float theta1 = (2.0f * glm::pi<float>() * i) / numVertices;
		float theta2 = (2.0f * glm::pi<float>() * (i + 1)) / numVertices;

		glm::vec4 p1 = center + glm::vec4(radius * cos(theta1), 0, radius * sin(theta1), 0);
		glm::vec4 p2 = center + glm::vec4(radius * cos(theta2), 0, radius * sin(theta2), 0);

		tigl::addVertex(Vertex::PC(center, cyan));
		tigl::addVertex(Vertex::PC(p1, cyan));
		tigl::addVertex(Vertex::PC(p2, cyan));
	}

	tigl::end();
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		int width, height;
		glfwGetWindowSize(window, &width, &height);

		// Read the pixel at the center of the screen
		unsigned char* pixel = new unsigned char[3];
		glReadPixels(width / 2, height / 2, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

		clickedPixel[0] = pixel[0];
		clickedPixel[1] = pixel[1];
		clickedPixel[2] = pixel[2];

		delete[] pixel;
	}
}