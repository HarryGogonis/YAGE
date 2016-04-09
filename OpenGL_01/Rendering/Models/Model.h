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
	Model(Transform* t);
	virtual ~Model();

	void SetProgram(GLuint) override;
	void SetShadowProgram(GLuint) override;
	void Destroy() override;

	virtual std::vector<VertexFormat> GetVertices() = 0;

	GLuint GetVao() const;
	const std::vector<GLuint>& GetVbos() const;
	
	const GLuint GetTexture(const std::string&) const override;
	void SetTexture(const std::string& textureName, const TextureType& textureType, const GLuint& texture) override;

protected:
	Transform* transform;
	GLuint vao;
	std::vector<GLuint> vbos;
	std::vector<Texture> textures;
};
