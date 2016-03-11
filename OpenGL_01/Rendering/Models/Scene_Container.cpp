#include "Scene_Container.h"
#include <SOIL.h>


Scene_Container::Scene_Container(const std::string &path)
{
	Assimp::Importer importer;

	scene = importer.ReadFile(path,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType |
		aiProcess_GenSmoothNormals);

	if (!scene)
	{
		perror(importer.GetErrorString());
		return;
	}

	for (int i = 0; i != scene->mNumMeshes; ++i)
	{
		aiMesh *mesh = scene->mMeshes[i];
		if (scene->mNumMaterials)
		{
			addMeshWithMat(mesh, scene->mMaterials[mesh->mMaterialIndex], path);
		}
		else
		{
			addMeshWithMat(mesh, nullptr, path);
		}
	}
}


Scene_Container::~Scene_Container()
{
	for (int i = 0; i != meshes.size(); ++i)
	{
		delete meshes[i];
	}
}

void Scene_Container::Destroy()
{}


void Scene_Container::Draw()
{
	for (int i = 0; i != meshes.size(); ++i)
	{
		meshes[i]->Draw();
	}
}

void Scene_Container::Update()
{
	for (int i = 0; i != meshes.size(); ++i)
	{
		meshes[i]->Update();
	}
}

std::vector<VertexFormat> Scene_Container::GetVertices()
{
	// do absolutely nothing; meshes keep track of vertices
	std::vector<VertexFormat> ret;
	return ret;
}


void Scene_Container::SetMeshPrograms(GLuint program)
{
	for (int i = 0; i != meshes.size(); ++i)
	{
		meshes[i]->SetProgram(program);
		meshes[i]->Create();
	}
}

void Scene_Container::SetUniformTexture(const std::string & fPath)
{
	for (int i = 0; i != meshes.size(); ++i)
	{
		meshes[i]->SetTexture(fPath.c_str(), SOIL_load_OGL_texture(
			fPath.c_str(),
			SOIL_LOAD_AUTO,
			1,
			SOIL_FLAG_MIPMAPS));
	}
}

void Scene_Container::addMeshWithMat(const aiMesh* ai_mesh, const aiMaterial* ai_mat, const std::string& path)
{
	Mesh *mesh = new Mesh(ai_mesh, ai_mat, path);
	meshes.push_back(mesh);
}

