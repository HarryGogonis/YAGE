#include "CustomObject.h"
#include "../../Managers/Models_Manager.h"
#include "SOIL.h"

CustomObject::CustomObject()
{
}

CustomObject::~CustomObject()
{
}

std::vector<VertexFormat> CustomObject::GetVertices()
{
	std::vector<VertexFormat> out;
	for (int i = 0; i < vertices.size(); i++)
	{
		out.push_back(
			VertexFormat(vertices[i], uvs[i])
		);
	}
	return out;
}

CustomObject::CustomObject(const char* objectPath, const char* texturePath)
{
	//TODO pass in transform
	transform = Transform(
		glm::vec4(50, 0, 0, 1),
		glm::vec4(1, 1, 1, 1),
		Quaternion()
		);
	this->objectPath = objectPath;
	this->texturePath = texturePath;
}

void CustomObject::Update()
{
	glm::mat4 scale = this->transform.getScaleMatrix();
	glm::mat4 rotation = this->transform.getRotationMatrix();
	glm::mat4 ViewMatrix = Camera::GetViewMatrix();
	glm::mat4 ProjectionMatrix = Camera::GetProjectionMatrix();
	glm::mat4 ModelMatrix = scale * rotation;
	glm::mat4 mvp = ProjectionMatrix * ViewMatrix * ModelMatrix;
	
	// Send transformation to currently bound shader
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
}

void CustomObject::Draw()
{
	glUseProgram(program);
	
	// Draw triangles
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

void CustomObject::Destroy()
{
	Model::Destroy();
	glDeleteTextures(1, &TextureID);
}

void CustomObject::Create()
{
	GLuint vao;
	GLuint vbo;

	// Load .bmp
	GLuint Texture = SOIL_load_OGL_texture
		(
			texturePath,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);
	Models_Manager::LoadObject(objectPath, vertices, uvs, normals);

	// Get handlers
	GLuint TextureID = glGetUniformLocation(program, "myTextureSampler");
	GLuint MatrixID = glGetUniformLocation(program, "MVP");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices = GetVertices();
	for (auto v : vertices)
	{
		std::cout << v << std::endl;
	}

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), nullptr);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),
		(void*)(offsetof(VertexFormat, VertexFormat::uv)));

	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glUniform1i(TextureID, 0);

	//here we assign the values
	this->vao = vao;
	this->vbos.push_back(vbo);
}
