#include "Mesh.h"
#include "../../Managers/Models_Manager.h"
#include "GL/glew.h"
#include "SOIL.h"
#include <string>
#include <sstream>

glm::vec3 assimpToGLM3D(const aiVector3D &vec)
{
	return glm::vec3(vec.x, vec.y, vec.z);
}

glm::vec2 assimpToGLM2D(const aiVector3D &vec)
{
	return glm::vec2(vec.x, vec.y);
}

Mesh::Mesh(const aiMesh* ai_mesh, const aiMaterial* ai_mat, const std::string& sFilePath)
{
	shininess = 20;
	strength = 10;
	for (auto i = 0; i < ai_mesh->mNumFaces; ++i)
	{
		const aiFace &face = ai_mesh->mFaces[i];
		for (int k = 0; k != 3; ++k) // We know face is always triangle
		{
			indices.push_back(face.mIndices[k]);
		}
	}
	for (auto i = 0; i != ai_mesh->mNumVertices; ++i)
	{
		vertices.push_back(assimpToGLM3D(ai_mesh->mVertices[i]));
		normals.push_back(assimpToGLM3D(ai_mesh->mNormals[i]));
		uvs.push_back(assimpToGLM2D(ai_mesh->mTextureCoords[0][i]));
	}
	if (ai_mat)
	{
		aiString path;
		for (int i = 0; i < ai_mat->GetTextureCount(aiTextureType_DIFFUSE); ++i)
		{
			if (ai_mat->GetTexture(
					aiTextureType_DIFFUSE, 
					i, 
					&path) == AI_SUCCESS)
			{
				// Add texture to total textures for this mesh
				// Note: Automatically assume diffuse (TODO: CHANGE!)
				GLuint textureID = SOIL_load_OGL_texture(
					path.C_Str(),
					SOIL_LOAD_AUTO,
					1,
					SOIL_FLAG_MIPMAPS);
				SetTexture("diffuse_" + textureID, Texture_Diffuse, textureID);
			}
			if (ai_mat->Get(AI_MATKEY_SHININESS, shininess) != AI_SUCCESS)
			{
				shininess = 20;
			}
			if (ai_mat->Get(AI_MATKEY_SHININESS_STRENGTH, strength) != AI_SUCCESS)
			{
				strength = 10;
			}
		}
	}
}

Mesh::~Mesh()
{
}

std::vector<VertexFormat> Mesh::GetVertices()
{
	std::vector<VertexFormat> out;
	for (int i = 0; i < vertices.size(); i++)
	{
		out.push_back(
			VertexFormat(vertices[i], uvs[i], normals[i])
		);
	}
	return out;
}

void Mesh::Update()
{
	glm::mat4 scale = this->transform.getScaleMatrix();
	glm::mat4 rotation = this->transform.getRotationMatrix();
	glm::mat4 translation = this->transform.getTranslationMatrix();
	glm::mat4 ViewMatrix = Camera::GetViewMatrix();
	glm::mat4 ProjectionMatrix = Camera::GetProjectionMatrix();
	glm::mat4 ModelMatrix = scale * rotation;

	// Send mvp to currently bound shader
	glm::mat4 mv = ViewMatrix * ModelMatrix;
	glm::mat4 mvp = ProjectionMatrix * ViewMatrix * ModelMatrix;
	glUniformMatrix4fv(MV_ID, 1, GL_FALSE, &mv[0][0]);
	glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, &mvp[0][0]);

	// Send normal matrix to currently bound shader
	glm::mat3 NormalMatrix = glm::mat3(glm::transpose(glm::inverse(ModelMatrix)));
	glUniformMatrix3fv(NormalMatrix_ID, 1, GL_FALSE, &NormalMatrix[0][0]);
}

void Mesh::Draw()
{	
	glUseProgram(program);

	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	GLuint i = 0;
	glUniform1f(glGetUniformLocation(program, "texture_count"), textures.size());
	if (textures.size() >= 3)
	{
		GLfloat intensity[3] = { 0.33333f, 0.33333f, 0.33333f };
		glUniform1fv(glGetUniformLocation(program, "diffuse_texture_contributions"), 3, intensity);
	}
	else if (textures.size() == 2)
	{
		GLfloat intensity[3] = { 0.5f, 0.5f, 0.0f };
		glUniform1fv(glGetUniformLocation(program, "texture_contributions"), 3, intensity);
	}
	else
	{
		GLfloat intensity[3] = { 1.0f, 0.0f, 0.0f };
		glUniform1fv(glGetUniformLocation(program, "texture_contributions"), 3, intensity);
	}
	for (; i < this->textures.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		// Retrieve texture number
		std::stringstream ss;
		std::string number;
		std::string type_string;
		TextureType ttype = textures[i].type;
		if (ttype == Texture_Diffuse)
		{
			ss << diffuseNr++;
			type_string = "texture_diffuse";
		}
		// We don't actually have real support for specular textures yet
		else if (ttype == Texture_Specular)
		{
			ss << specularNr++;
			type_string = "texture_specular";
		}
		number = ss.str();
		// Find appropriate diffuse or specular texture handle
		glUniform1f(glGetUniformLocation(program, (type_string + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	glActiveTexture(GL_TEXTURE0);

	glUniform1f(glGetUniformLocation(program, "Shininess"), shininess);
	glUniform1f(glGetUniformLocation(program, "Strength"), strength);

	// Draw triangles
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, nullptr);
	glBindVertexArray(0);
}

void Mesh::Create()
{
	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	// Get handlers
	MVP_ID = glGetUniformLocation(program, "MVP");
	MV_ID = glGetUniformLocation(program, "MV");
	NormalMatrix_ID = glGetUniformLocation(program, "NormalMatrix");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	std::vector<VertexFormat> vertices = GetVertices();

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(VertexFormat) * vertices.size(),
		&vertices[0],
		GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(unsigned short) * indices.size(),
		&indices[0],
		GL_STATIC_DRAW);

	// Attribute buffer - Vertex
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		sizeof(VertexFormat), nullptr);

	// Attribute buffer - UV
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		sizeof(VertexFormat),
		(void*)(offsetof(VertexFormat, VertexFormat::uv)));

	// Attribute buffer - Normal
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
		sizeof(VertexFormat),
		(void*)(offsetof(VertexFormat, VertexFormat::normal)));

	glBindVertexArray(0);

	//here we assign the values
	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);
}
