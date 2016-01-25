#include "Model.h"

Model::Model()
{

}

Model::Model(Transform t, Color c)
{
	this->transform = t;
	this->color = c;
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

void Model::Destroy()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(vbos.size(), &vbos[0]);
	vbos.clear();
}