#pragma once
#include "Model.h"
#include <vector>

class CustomObject : public Model
{
public:
	CustomObject();
	CustomObject(const std::string&, const std::string&);
	~CustomObject();

	std::vector<VertexFormat> GetVertices() override final;
	
	void Create();
	virtual void Draw() override final;
	virtual void Destroy() override final;
	virtual void Update() override final;
	virtual void SetTexture(const std::string&, GLuint) override;
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<unsigned short> indices;
	
	GLuint MatrixID;
	GLuint TextureID;

	std::string objectPath;
	std::string texturePath;
};

