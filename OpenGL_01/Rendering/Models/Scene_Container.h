#pragma once
#include "Model.h"
#include "Mesh.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

class Scene_Container : public IGameObject
{
public:
	Scene_Container(const std::string&);
	~Scene_Container();

	void Draw() override;
	void Update() override;
	void Destroy() override;
	void SetProgram(GLuint) override;

	void SetTexture(const std::string&,const TextureType&, const GLuint&) override;
	const GLuint GetTexture(const std::string&) const override;

private:
	std::vector<Mesh*> meshes;
	const aiScene *scene;

	void addMeshWithMat(const aiMesh*, const aiMaterial*, const std::string&);
};

