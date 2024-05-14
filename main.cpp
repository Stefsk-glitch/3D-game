#include "tigl.h"
#include "cam.h"

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

void init();
void update(float deltaTime);
void draw();
std::vector<Vertex> buildCube(const glm::vec3& p, const glm::vec3& s, const glm::vec4& color);

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
}


void update(float deltaTime)
{
	camera->update(window, deltaTime);
}

void draw()
{
	glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 100.0f);

	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setViewMatrix(camera->getMatrix());
	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	tigl::shader->enableColor(true);

	glEnable(GL_DEPTH_TEST);

	tigl::begin(GL_TRIANGLES);

	// rainbow traingle
	/*tigl::addVertex(Vertex::PC(glm::vec3(-2, -1, -4), glm::vec4(1, 0, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(2, -1, -4), glm::vec4(0, 1, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(0, 1, -4), glm::vec4(0, 0, 1, 1)));*/

	// square first traingle
	tigl::addVertex(Vertex::PC(glm::vec3(-10, -1, -10), glm::vec4(1, 1, 1, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(-10, -1, 10), glm::vec4(1, 1, 1, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(10, -1, 10), glm::vec4(1, 1, 1, 1)));

	// square second traingle
	tigl::addVertex(Vertex::PC(glm::vec3(-10, -1, -10), glm::vec4(1, 1, 1, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(10, -1, -10), glm::vec4(1, 1, 1, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(10, -1, 10), glm::vec4(1, 1, 1, 1)));

	tigl::end();

	std::vector<Vertex> verts;

	// vec3(x, y, z)
	auto cube = buildCube(glm::vec3(0, 0, -10), glm::vec3(0.5, 0.5, 0.5), glm::vec4(1, 0, 0, 1));

	verts.insert(verts.end(), cube.begin(), cube.end());
	tigl::drawVertices(GL_QUADS, verts);
	glDisable(GL_DEPTH_TEST);

	
}

std::vector<Vertex> buildCube(const glm::vec3& p, const glm::vec3& s, const glm::vec4& color)
{
	std::vector<Vertex> verts;

	// Bottom face
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x, -s.y, -s.z), color, glm::vec2(0, 0), glm::vec3(0, -1, 0))); // Bottom-left-back vertex
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x, -s.y, -s.z), color, glm::vec2(1, 0), glm::vec3(0, -1, 0)));  // Bottom-right-back vertex
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x, -s.y, s.z), color, glm::vec2(1, 1), glm::vec3(0, -1, 0)));   // Bottom-right-front vertex
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x, -s.y, s.z), color, glm::vec2(0, 1), glm::vec3(0, -1, 0)));  // Bottom-left-front vertex

	// Top face
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x, s.y, -s.z), color, glm::vec2(0, 0), glm::vec3(0, 1, 0)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x, s.y, -s.z), color, glm::vec2(1, 0), glm::vec3(0, 1, 0)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x, s.y, s.z), color, glm::vec2(1, 1), glm::vec3(0, 1, 0)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x, s.y, s.z), color, glm::vec2(0, 1), glm::vec3(0, 1, 0)));

	// Left face
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x, -s.y, -s.z), color, glm::vec2(0, 0), glm::vec3(1, 0, 0)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x, s.y, -s.z), color, glm::vec2(1, 0), glm::vec3(1, 0, 0)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x, s.y, s.z), color, glm::vec2(1, 1), glm::vec3(1, 0, 0)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x, -s.y, s.z), color, glm::vec2(0, 1), glm::vec3(1, 0, 0)));

	// Right face
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x, -s.y, -s.z), color, glm::vec2(0, 0), glm::vec3(-1, 0, 0)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x, s.y, -s.z), color, glm::vec2(1, 0), glm::vec3(-1, 0, 0)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x, s.y, s.z), color, glm::vec2(1, 1), glm::vec3(-1, 0, 0)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x, -s.y, s.z), color, glm::vec2(0, 1), glm::vec3(-1, 0, 0)));

	// Back face
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x, -s.y, -s.z), color, glm::vec2(0, 0), glm::vec3(0, 0, -1)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x, s.y, -s.z), color, glm::vec2(1, 0), glm::vec3(0, 0, -1)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x, s.y, -s.z), color, glm::vec2(1, 1), glm::vec3(0, 0, -1)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x, -s.y, -s.z), color, glm::vec2(0, 1), glm::vec3(0, 0, -1)));

	// Front face
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x, -s.y, s.z), color, glm::vec2(0, 0), glm::vec3(0, 0, 1)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x, s.y, s.z), color, glm::vec2(1, 0), glm::vec3(0, 0, 1)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x, s.y, s.z), color, glm::vec2(1, 1), glm::vec3(0, 0, 1)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x, -s.y, s.z), color, glm::vec2(0, 1), glm::vec3(0, 0, 1)));

	return verts;
}
