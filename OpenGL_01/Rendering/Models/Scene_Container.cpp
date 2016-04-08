#include "Scene_Container.h"


Scene_Container::Scene_Container(const std::string &path, Transform transform)
{
	Assimp::Importer importer;

	this->transform = transform;
	scene = importer.ReadFile(path,
		aiProcess_CalcTangentSpace		|
		aiProcess_Triangulate			|
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType			|
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
			addMeshWithMat(mesh, scene->mMaterials[mesh->mMaterialIndex], transform);
		}
		else
		{
			addMeshWithMat(mesh, nullptr, transform);
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

void Scene_Container::SetProgram(GLuint program)
{
	this->program = program;
	for (int i = 0; i != meshes.size(); ++i)
	{
		meshes[i]->SetProgram(program);
		meshes[i]->Create();
	}
}

void Scene_Container::SetShadowProgram(GLuint program)
{
	this->shadowProgram = program;
	for (int i = 0; i != meshes.size(); ++i)
	{
		meshes[i]->SetShadowProgram(program); // ?? do we really need to do this?
	}
}

void Scene_Container::SetTexture(const std::string& textureName, const TextureType& textureType, const GLuint& id)
{
	for (int i = 0; i != meshes.size(); ++i)
	{
		meshes[i]->SetTexture(textureName, textureType, id);
	}
}

const GLuint Scene_Container::GetTexture(const std::string &name) const
{
	GLuint retval = 0;
	Texture *t = nullptr;
	for (int i = 0; i != meshes.size(); ++i)
	{
		retval = meshes[i]->GetTexture(name);
		if (retval)
			return retval;
	}
	std::cout << "ERROR: Scene_Container cannot find texture" << std::endl;
	return retval;
}

void Scene_Container::Draw()
{
	Draw(program);
}

void Scene_Container::DrawShadow()
{
	DrawShadow(shadowProgram);
}

void Scene_Container::Draw(GLuint program)
{
	for (int i = 0; i != meshes.size(); ++i)
	{
		meshes[i]->Draw(program);
	}
}

void Scene_Container::DrawShadow(GLuint program)
{
	for (int i = 0; i != meshes.size(); ++i)
	{
		meshes[i]->DrawShadow(program);
	}
}

void Scene_Container::Update()
{
	for (int i = 0; i != meshes.size(); ++i)
	{
		meshes[i]->Update();
	}
}

void Scene_Container::addMeshWithMat(const aiMesh* ai_mesh, const aiMaterial* ai_mat, const Transform& t)
{
	Mesh *mesh = new Mesh(ai_mesh, ai_mat, t);
	meshes.push_back(mesh);
}

