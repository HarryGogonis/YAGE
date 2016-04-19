#pragma once
#include "../IGameObject.h"
class Skybox :
	public IGameObject
{
public:
	static Skybox* GetInstance();

	// depricated
	void SetTexture(const std::string& textureName, const TextureType& textureType, const GLuint& texture) override {};
	const GLuint GetTexture(const std::string& textureName) const override { return texture; };

	void Draw();
	void Draw(GLuint) override;
	void DrawShadow() {};
	void DrawShadow(GLuint) override {};
	void Update() override;
	void Destroy() override;

	void SetCubemap(const std::string&);
private:
	static Skybox* mSkybox;
	Skybox();
	GLuint vertex_buffer, vao, texture;
	GLuint Texture_ID, V_ID, P_ID;
};

