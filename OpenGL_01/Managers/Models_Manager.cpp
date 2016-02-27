#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Models_Manager.h"
#include "../Rendering/Models/CustomObject.h"
#include "../Rendering/Util/Light.h"

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

/*
 * Read in blender object (.obj) file
 * http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
 */
bool Models_Manager::LoadObject(const std::string& path, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals)
{
	// temp storage
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	// open file
	std::ifstream file(path);
	std::string line;

	// read file
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string lineHeader;

		iss >> lineHeader;

		// v is a vertex
		if (lineHeader == "v")
		{
			double x, y, z;
			iss >> x >> y >> z;
			temp_vertices.push_back(glm::vec3(x,y,z));
		}
		// vt is a texture coordinate
		else if (lineHeader == "vt")
		{
			glm::vec2 uv;
			double x, y;
			iss >> x >> y;
			temp_uvs.push_back(glm::vec2(x,y));
		}
		// vn is a texture normal
		else if (lineHeader == "vn")
		{
			double x, y, z;
			iss >> x >> y >> z;
			temp_normals.push_back(glm::vec3(x,y,z));
		}
		// f is a face
		else if (lineHeader == "f")
		{
			std::string t1, t2, t3;
			std::vector<std::string> buffer1, buffer2, buffer3;
			char delim = '/';

			iss >> t1 >> t2 >> t3;

			split(t1,delim, buffer1);
			split(t2,delim, buffer2);
			split(t3,delim, buffer3);

			vertexIndices.push_back( 
				std::stoi(buffer1[0]));
			uvIndices.push_back(
				std::stoi(buffer1[1]));
			normalIndices.push_back(
				std::stoi(buffer1[2]));

			vertexIndices.push_back( 
				std::stoi(buffer2[0]));
			uvIndices.push_back(
				std::stoi(buffer2[1]));
			normalIndices.push_back(
				std::stoi(buffer2[2]));
			
			vertexIndices.push_back( 
				std::stoi(buffer3[0]));
			uvIndices.push_back(
				std::stoi(buffer3[1]));
			normalIndices.push_back(
				std::stoi(buffer3[2]));
		}
		// Most likely a comment or some other garbage
		else
		{
		}
	}

	// Iterate through each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Put the attributes in buffers
		out_vertices.push_back(temp_vertices[vertexIndex - 1]);
		out_uvs.push_back(temp_uvs[uvIndex - 1]);
		out_normals.push_back(temp_normals[normalIndex - 1]);
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