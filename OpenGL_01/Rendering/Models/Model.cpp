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
	const Texture *t = nullptr;
	for (int i = 0; i != textures.size(); ++i)
	{
		if (textures[i].name == textureName)
		{
			t = &textures[i];
			break;
		}
	}
	if (!t)
	{
		std::cout << "Error finding texture " << textureName << std::endl;
		return 0;
	}
	return t->id;
}

void Model::SetTexture(const std::string& textureName, const TextureType& textureType, const GLuint& texture)
{
	if (texture == 0) return;
	Texture t = {
		texture,
		textureName,
		textureType
	};
	textures.push_back(t);
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
