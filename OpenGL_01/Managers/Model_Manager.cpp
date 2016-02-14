#include "Models_Manager.h"

Models_Manager::Models_Manager()
{
	Quad* quad1 = new Quad(Transform(
		glm::vec4(0, 0, 0, 1),
		glm::vec4(1, 1, 1, 1),
		Quaternion()
		), Color::RED);
	quad1->SetProgram(Shader_Manager::GetShader("colorShader"));
	quad1->Create();
	gameModelList["quad1"] = quad1;

	Quad* quad2 = new Quad(Transform(
		glm::vec4(5, 0, 0, 1),
		glm::vec4(1, 1, 1, 1),
		Quaternion()
		), Color::RED);
	quad2->SetProgram(Shader_Manager::GetShader("colorShader"));
	quad2->Create();
	gameModelList["quad2"] = quad2;

	Quad* quad3 = new Quad(Transform(
		glm::vec4(-5, 0, 0, 1),
		glm::vec4(1, 1, 1, 1),
		Quaternion()
		), Color::RED);
	quad3->SetProgram(Shader_Manager::GetShader("colorShader"));
	quad3->Create();
	gameModelList["quad3"] = quad3;
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

/*
 * Read in a BMP texture file
 */
GLuint Models_Manager::LoadTexture(const char * filename)
{
	/* 
	 * http://stackoverflow.com/a/12524013/3134975
	 * http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/
	*/
	GLuint texture;

	unsigned char * data;
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char header[54];

	// Open File
	FILE * file = fopen(filename, "rb");
	if (file == NULL)
	{
		std::cerr << "Error opening image: " << filename << std::endl;
		return 0;
	}
	// Check file headers
	if (fread(header, 1, 54, file) != 54)
	{
		std::cerr << "Invalid BMP file: " << filename << std::endl;
		return 0;
	}
	if (header[0] != 'B' || header[1] != 'M')
	{
		std::cerr << "Invalid BMP file: " << filename << std::endl;
		return 0;
	}

	// Setup image parameters
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);
	if (imageSize == 0) imageSize = width * height * 3;
	if (dataPos == 0)	dataPos = 54;

	// Create a buffer for data
	data = new unsigned char[imageSize];

	// Read data from file to buffer
	fread(data, 1, imageSize, file); 
	fclose(file);

	// Pass data to OpenGL
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	// Clear buffer
	delete[] data;

	// Trilinear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	return texture;
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