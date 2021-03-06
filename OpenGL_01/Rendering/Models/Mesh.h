#pragma once
#include "Model.h"
#include <assimp/scene.h>
#include <vector>

class Mesh : public Model
{
public:
	Mesh(const std::string&, const aiMesh*, const aiMaterial*, Transform*);
	Mesh(const Mesh*, Transform*);
	~Mesh();

	std::vector<VertexFormat> GetVertices() override final;
	
	void Create();
	void DrawShadow(GLuint) override final;
	void Draw(GLuint) override final;
	void Update() override final;
	std::vector<glm::vec3> GetPositionVertices();

	float shininess;
	float strength;
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;
	std::vector<unsigned short> indices;

	glm::mat4 ModelMatrix;
	
	GLuint MVP_ID, MV_ID, Trans_ID, Depth_ID, ScaleConst_ID;

	std::string objectPath;
	std::string texturePath;
};

