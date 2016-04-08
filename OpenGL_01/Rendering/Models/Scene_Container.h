#pragma once
#include "Model.h"
#include "Mesh.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

class Scene_Container : public IGameObject
{
public:
	Scene_Container(const std::string&, Transform);
	~Scene_Container();

	// Draw function so that we are sure that the Scene_Container uses its own program
	void Draw();
	void Draw(GLuint) override;
	void DrawShadow();
	void DrawShadow(GLuint) override;
	void Update() override;
	void Destroy() override;

	void SetProgram(GLuint) override;
	void SetShadowProgram(GLuint) override;

	GLuint GetShadowProgram() const
	{
		return shadowProgram;
	}

	void SetTexture(const std::string&,const TextureType&, const GLuint&) override;
	const GLuint GetTexture(const std::string&) const override;

	Transform transform;
private:
	std::vector<Mesh*> meshes;
	const aiScene *scene;
	int texture_id = 0;

	GLuint shadowProgram;

	void addMeshWithMat(const aiMesh*, const aiMaterial*, const Transform&);
};

