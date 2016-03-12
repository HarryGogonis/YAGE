#pragma once
#include <vector>
#include "../IGameObject.h"
#include "../VertexFormat.h"
#include "../Util/Camera.h"

class Model :public IGameObject
{
public:
	Model();
	Model(Transform t);
	virtual ~Model();

	virtual void Draw() override;
	virtual void Update() override;
	virtual void SetProgram(GLuint shaderName) override;
	virtual void Destroy() override;

	virtual std::vector<VertexFormat> GetVertices() = 0;

	GLuint GetVao() const;
	const std::vector<GLuint>& GetVbos() const;
	
	virtual const GLuint GetTexture(const std::string&) const override;
	virtual void SetTexture(const std::string&, GLuint) override;
	
	Transform transform;

protected:
	GLuint vao;
	GLuint program;
	std::vector<GLuint> vbos;
	std::map<std::string, GLuint> textures;
	


};