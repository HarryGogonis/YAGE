#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Models_Manager.h"
#include "../Rendering/Models/CustomObject.h"
#include "../Rendering/Util/Light.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

Models_Manager::Models_Manager()
{
	CustomObject* suzanne = new CustomObject("Examples\\suzanne.obj", "Examples\\suzanne.dds");
	suzanne->SetProgram(Shader_Manager::GetShader("textureShader"));
	suzanne->transform.SetScale(glm::vec3(0.5f));
	suzanne->transform.SetPosition(glm::vec3(0.0, 0.5, 0.0));
	suzanne->Create();
	gameModelList["suzanne"] = suzanne;

	CustomObject* cube1 = new CustomObject("Examples\\cube.obj", "Examples\\Crate.bmp");
	cube1->SetProgram(Shader_Manager::GetShader("textureShader"));
	cube1->transform.SetScale(glm::vec3(0.2f));
	cube1->transform.SetPosition(glm::vec3(1.0, 0.2, -2.5));
	cube1->Create();
	gameModelList["cube1"] = cube1;

	CustomObject* cube2 = new CustomObject("Examples\\cube.obj", "Examples\\Crate.bmp");
	cube2->SetProgram(Shader_Manager::GetShader("textureShader"));
	cube2->transform.SetScale(glm::vec3(0.2f));
	cube2->transform.SetPosition(glm::vec3(1.0, 0.2, 2.5));
	cube2->Create();
	gameModelList["cube2"] = cube2;

	CustomObject* cube3 = new CustomObject("Examples\\cube.obj", "Examples\\Crate.bmp");
	cube3->SetProgram(Shader_Manager::GetShader("textureShader"));
	cube3->transform.SetScale(glm::vec3(0.2f));
	cube3->transform.SetPosition(glm::vec3(-1.0, 0.2, -2.5));
	cube3->Create();
	gameModelList["cube3"] = cube3;

	CustomObject* cube4 = new CustomObject("Examples\\cube.obj", "Examples\\Crate.bmp");
	cube4->SetProgram(Shader_Manager::GetShader("textureShader"));
	cube4->transform.SetScale(glm::vec3(0.2f));
	cube4->transform.SetPosition(glm::vec3(-1.0, 0.2, 2.5));
	cube4->Create();
	gameModelList["cube4"] = cube4;

	// floor
	CustomObject* cube5 = new CustomObject("Examples\\cube.obj", "Examples\\checkerboard.dds");
	cube5->SetProgram(Shader_Manager::GetShader("textureShader"));
	cube5->transform.SetPosition(glm::vec3(0.0, 0.0, 0.0));
	cube5->transform.SetScale(glm::vec3(5.0, 0.0001, 5.0));
	cube5->shininess = 0.5;
	cube5->Create();
	gameModelList["cube5"] = cube5;

	// back wall
	CustomObject* cube6 = new CustomObject("Examples\\cube.obj", "Examples\\checkerboard.dds");
	cube6->SetProgram(Shader_Manager::GetShader("textureShader"));
	cube6->transform.SetPosition(glm::vec3(0.0, 0.0, -5.0));
	cube6->transform.RotateX(90);
	cube5->shininess = 0.5;
	cube6->transform.SetScale(glm::vec3(5.0, 0.0001, 5.0));
	cube6->Create();
	gameModelList["cube6"] = cube6;

	Light* pointLight1 = new PointLight(
		glm::vec3(0.6, 0.5, 0.5), // color
		glm::vec3(0.0, 4.0, 0.0) // position
		); 
	pointLight1->SetProgram(Shader_Manager::GetShader("textureShader"));
	pointLight1->SetAttenuation(0.0, 0.0, 1.0);
	pointLight1->Create();
	gameModelList["light1"] = pointLight1;

	Light* directionalLight1 = new DirectionalLight(
		glm::vec3(0.2, 0.2, 0.2), // color
		glm::vec3(0.0, 0.0, 1.0), // direction
		glm::vec3(0.5, 0.5, 0.5) // half vec
		);
	directionalLight1->SetProgram(Shader_Manager::GetShader("textureShader"));
	directionalLight1->Create();
	gameModelList["light2"] = directionalLight1;

	Light* ambientLight1 = new AmbientLight(glm::vec3(1.0, 1.0, 1.0), 0.05);
	ambientLight1->SetProgram(Shader_Manager::GetShader("textureShader"));
	ambientLight1->Create();
	gameModelList["light3"] = ambientLight1;
}

Models_Manager::~Models_Manager()
{
	// iterate through map
	for (auto model : gameModelList)
	{
		delete model.second;
	}
	gameModelList.clear();
}

void Models_Manager::DeleteModel(const std::string& gameModelName)
{
	IGameObject* model = gameModelList[gameModelName];
	model->Destroy();
	gameModelList.erase(gameModelName);
}

const IGameObject& Models_Manager::GetModel(const std::string& gameModelName)
{
	return (*gameModelList.at(gameModelName));
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

glm::vec3 assimpToGLM3D(const aiVector3D &vec)
{
	return glm::vec3(vec.x, vec.y, vec.z);
}

glm::vec2 assimpToGLM2D(const aiVector3D &vec)
{
	return glm::vec2(vec.x, vec.y);
}

/*
 * Read in any file format with assimp
 */
bool Models_Manager::LoadObject(const std::string& path, 
	std::vector<glm::vec3>& out_vertices, 
	std::vector<glm::vec2>& out_uvs, 
	std::vector<glm::vec3>& out_normals, 
	std::vector<unsigned short>& out_indices)
{
	Assimp::Importer importer;

	const aiScene *scene = importer.ReadFile(path,
		aiProcess_CalcTangentSpace		|
		aiProcess_Triangulate			|
		aiProcess_JoinIdenticalVertices	|
		aiProcess_SortByPType);

	if (!scene)
	{
		perror(importer.GetErrorString());
		return false;
	}

	// Does not keep track of separate meshes for material rendering
	// TODO: Fix http://www.mbsoftworks.sk/index.php?page=tutorials&series=1&tutorial=23
	for (int i = 0; i != scene->mNumMeshes; ++i)
	{
		aiMesh *mesh = scene->mMeshes[i];
		for (int j = 0; j != mesh->mNumFaces; ++j)
		{
			const aiFace &face = mesh->mFaces[j];
			for (int k = 0; k != 3; ++k)
			{
				out_indices.push_back(face.mIndices[k]);
			}
		}
		for (int j = 0; j != mesh->mNumVertices; ++j) {
			out_vertices.push_back(assimpToGLM3D(mesh->mVertices[j]));
			if (mesh->HasNormals())
			{
				out_normals.push_back(assimpToGLM3D(mesh->mNormals[j]));
			}
			else
			{
				out_normals.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
			}
			out_uvs.push_back(assimpToGLM2D(mesh->mTextureCoords[0][j]));
		}
	}

	return true;
}

void Models_Manager::Update()
{
	// iterate through model list and Update
	for (auto model : gameModelList)
	{
		model.second->Update();
	}
}

void Models_Manager::Draw()
{
	// iterate through model list and Draw
	for (auto model : gameModelList)
	{
		model.second->Draw();
	}
}