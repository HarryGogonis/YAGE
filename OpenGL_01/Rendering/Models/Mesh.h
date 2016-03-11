#pragma once
#include "Model.h"
#include <assimp/scene.h>
#include <vector>

class Mesh : public Model
{
public:
	Mesh(const aiMesh*, const aiMaterial*, const std::string&);
	~Mesh();

	std::vector<VertexFormat> GetVertices() override final;
	
	void Create();
	virtual void Draw() override final;
	virtual void Update() override final;
	virtual void SetTexture(const std::string&, GLuint) override;
	void SetDiffuseTexture(GLuint);

	float shininess;
	float strength;
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<unsigned short> indices;

	glm::mat4 ModelMatrix;
	
	GLuint MVP_ID, MV_ID;
	GLuint NormalMatrix_ID;

	std::string objectPath;
	std::string texturePath;
};

