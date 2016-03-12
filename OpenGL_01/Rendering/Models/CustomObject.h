#pragma once
#include "Model.h"
#include "../Util/Material.h"
#include <vector>

class CustomObject : public Model
{
public:
	CustomObject();
	CustomObject(const char*, const char*);
	~CustomObject();

	std::vector<VertexFormat> GetVertices();
	void Create();
	virtual void Draw() override final;
	virtual void Destroy() override final;
	virtual void Update() override final;
	virtual void SetTexture(const std::string&, GLuint) override;

	float shininess;
	float strength;
	Material material;
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<unsigned short> indices;

	// Uniform variable locations
	GLuint MVP_ID, MV_ID;
	GLuint Texture_ID;
	GLuint NormalMatrix_ID;
	GLuint EyeDirection_ID;

	std::string objectPath;
	std::string texturePath;
};

