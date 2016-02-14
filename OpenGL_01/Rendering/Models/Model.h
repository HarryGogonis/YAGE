#pragma once
#include <vector>
#include "../IGameObject.h"
#include "../VertexFormat.h"

class Model :public IGameObject
{
public:
	Model();
	Model(Transform t, Color c);
	virtual ~Model();

	virtual void Draw() override;
	virtual void Update() override;
	virtual void SetProgram(GLuint shaderName) override;
	virtual void Destroy() override;

	virtual std::vector<VertexFormat> GetVertices() = 0;
	virtual GLuint GetVao() const override;
	virtual const std::vector<GLuint>& GetVbos() const override;
	Transform transform;
	Color color;
protected:
	GLuint vao;
	GLuint program;
	std::vector<GLuint> vbos;


};