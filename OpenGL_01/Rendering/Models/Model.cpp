#include "Model.h"

Model::Model()
{

}

Model::Model(Transform t)
{
	this->transform = t;
}

Model::~Model()
{
	Destroy();
}

void Model::Draw()
{
	// override this
}

void Model::Update()
{
	// override this
}

void Model::SetProgram(GLuint program)
{
	this->program = program;
}

GLuint Model::GetVao() const
{
	return vao;
}

const std::vector<GLuint>& Model::GetVbos() const
{
	return vbos;
}

const GLuint Model::GetTexture(const std::string& textureName) const
{
//	if (textures.count(textureName) == 0)
//	{
//		std::cout << "Error finding texture " << textureName << std::endl;
//		return 0;
//	}
//	return textures.at(textureName);
	return 0;
}

void Model::SetTexture(const std::string& textureName, GLuint texture)
{
	if (texture == 0) return;
	//textures[textureName] = texture;
}

void Model::Destroy()
{
	if (!vbos.empty())
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(vbos.size(), &vbos[0]);
		vbos.clear();

		if (textures.size() > 0)
		{
			for (auto t : textures)
			{
				glDeleteTextures(1, &t.id);
			}
			textures.clear();
		}
	}
}
