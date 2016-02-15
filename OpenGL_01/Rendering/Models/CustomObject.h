#pragma once
#include "Model.h"
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
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	
	GLuint vertexbuffer;
	GLuint uvbuffer;

	GLuint MatrixID;
	GLuint Texture;
	GLuint TextureID;

	const char* objectPath;
	const char* texturePath;
};

