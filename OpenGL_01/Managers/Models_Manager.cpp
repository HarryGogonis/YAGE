#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Models_Manager.h"
#include "../Rendering/Models/CustomObject.h"
#include "../Rendering/Models/Quad.h"

Models_Manager::Models_Manager()
{
	CustomObject* cubeObj = new CustomObject("cube.obj", "uvmap.DDS");
	cubeObj->SetProgram(Shader_Manager::GetShader("textureShader"));
	cubeObj->Create();
	gameModelList["cubeObj"] = cubeObj;

	Quad* quad = new Quad(
		Transform(
			glm::vec4(0, 0, 0, 0),
			glm::vec4(5, 5, 1, 1),
			Quaternion(0.5, 0.25, 0.25, 0.25)
			),
		Color::WHITE);
	quad->SetProgram(Shader_Manager::GetShader("colorShader"));
	quad->Create();
	gameModelList["quad"] = quad;
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
bool Models_Manager::LoadObject(const char * path, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals)
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