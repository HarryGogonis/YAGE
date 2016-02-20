#pragma once
#include "Model.h"

class Cube :public Model
{
public:
	Cube(Transform t);
	~Cube();

	void Create();
	void Draw() override final;
	void Update() override final;

	std::vector<VertexFormat> GetVertices() override final;
	static std::vector<unsigned short> GetIndices();

	virtual void SetTexture(const std::string&, GLuint) override final;
private:
	GLuint MatrixID;
	GLuint TexureID;

	std::string textureName;
};