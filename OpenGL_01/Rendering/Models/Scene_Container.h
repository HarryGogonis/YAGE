#pragma once
#include "Model.h"
#include "Mesh.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

class Scene_Container : public Model
{
public:
	Scene_Container(const std::string&);
	~Scene_Container();

	virtual void Draw() override;
	virtual void Update() override;
	virtual void Destroy() override;

	// Should not be used; we need to redefine what a model entails
	virtual std::vector<VertexFormat> GetVertices() override;

	void SetMeshPrograms(GLuint program);

	void SetUniformTexture(const std::string&);

private:
	std::vector<Mesh*> meshes;
	const aiScene *scene;

	void addMeshWithMat(const aiMesh*, const aiMaterial*, const std::string&);
};

