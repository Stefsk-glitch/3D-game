#pragma once

#include "shape.h" 

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <list>

class Texture;

class ObjModel : public Shape
{
private:
	class Vertex
	{
	public:
		int position;
		int normal;
		int texcoord;
	};

	class Face
	{
	public:
		std::list<Vertex> vertices;
	};
	class MaterialInfo
	{
	public:
		MaterialInfo();
		std::string name;
		Texture* texture;
	};

	class ObjGroup
	{
	public:
		std::string name;
		int materialIndex;
		std::list<Face> faces;
	};


	std::vector<glm::vec3>	vertices;
	std::vector<glm::vec3>	normals;
	std::vector<glm::vec2>	texcoords;
	std::vector<ObjGroup*> groups;
	std::vector<MaterialInfo*> materials;

	void loadMaterialFile(const std::string& fileName, const std::string& dirName);
public:
	ObjModel(const std::string& filename);
	~ObjModel(void);

	std::vector<tigl::Vertex> verticesToDraw;

	glm::vec3 position; 
	float rotationAngleY;
	float rotationAngleX;

	virtual void update() override;
	virtual void draw() override;
};
