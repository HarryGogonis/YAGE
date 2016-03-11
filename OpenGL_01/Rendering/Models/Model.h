#pragma once
#include <vector>
#include <string>
#include <map>
#include "../IGameObject.h"
#include "../VertexFormat.h"
#include "../Texture.h"
#include "../Util/Camera.h"

class Model : public IGameObject
{
public:
	Model();
	Model(Transform t);
	virtual ~Model();

	void Draw() override;
	void Update() override;
	void SetProgram(GLuint shaderName) override;
	void Destroy() override;

	virtual std::vector<VertexFormat> GetVertices() = 0;

	GLuint GetVao() const;
	const std::vector<GLuint>& GetVbos() const;
	
	const GLuint GetTexture(const std::string&) const override;
	void SetTexture(const std::string& textureName, const TextureType& textureType, const GLuint& texture) override;

	Transform transform;
protected:
	GLuint vao;
	GLuint program;
	std::vector<GLuint> vbos;
	std::vector<Texture> textures;
	//std::map<std::string, GLuint> textures;


};
