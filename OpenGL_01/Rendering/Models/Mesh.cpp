#include "Mesh.h" 
#include "GL/glew.h"
#include "SOIL.h"
#include <assert.h>
#include "../../Managers/Shadow_Manager.h"
#include "../Util/Camera.h"

glm::vec3 assimpToGLM3D(const aiVector3D &vec)
{
	return glm::vec3(vec.x, vec.y, vec.z);
}

glm::vec2 assimpToGLM2D(const aiVector3D &vec)
{
	return glm::vec2(vec.x, vec.y);
}

Mesh::Mesh(const aiMesh* ai_mesh, const aiMaterial* ai_mat, Transform* transform)
{
	shininess = 2;
	strength = 2;
	this->transform = transform;

	assert(ai_mesh->HasTangentsAndBitangents());
	assert(ai_mesh->HasNormals());
	assert(ai_mesh->HasPositions());
	assert(ai_mesh->HasTextureCoords(0));

	for (auto i = 0; i < ai_mesh->mNumFaces; ++i)
	{
		const aiFace &face = ai_mesh->mFaces[i];
		for (int k = 0; k != 3; ++k) // We know face is always triangle w/ how we import
		{
			indices.push_back(face.mIndices[k]);
		}
	}
	for (auto i = 0; i != ai_mesh->mNumVertices; ++i)
	{
		vertices.push_back(assimpToGLM3D(ai_mesh->mVertices[i]));
		normals.push_back(assimpToGLM3D(ai_mesh->mNormals[i]));
		uvs.push_back(assimpToGLM2D(ai_mesh->mTextureCoords[0][i]));
		tangents.push_back(assimpToGLM3D(ai_mesh->mTangents[i]));
		bitangents.push_back(assimpToGLM3D(ai_mesh->mBitangents[i]));
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
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_INVERT_Y);
				if (!textureID)
					std::perror("ERROR: Mesh did not load material texture");
				else
					SetTexture("diffuse_" + textureID, Texture_Diffuse, textureID);
			}
			if (ai_mat->Get(AI_MATKEY_SHININESS, shininess) != AI_SUCCESS)
			{
				shininess = 20;
			}
			if (ai_mat->Get(AI_MATKEY_SHININESS_STRENGTH, strength) != AI_SUCCESS)
			{
				strength = 2;
			}
		}
	}
}

Mesh::Mesh(const Mesh* mesh, Transform* t)
{
	shininess = 2;
	strength = 2;
	this->transform = t;

	vertices = mesh->vertices;
	normals = mesh->normals;
	uvs = mesh->uvs;
	tangents = mesh->tangents;
	bitangents = mesh->bitangents;
	indices = mesh->indices;
	textures = mesh->textures;
}

Mesh::~Mesh()
{
	// We don't want this to delete the program, since it shares w/ container.
	// Is this poor programming? At least I have comments!
	program = 0;
}

std::vector<VertexFormat> Mesh::GetVertices()
{
	std::vector<VertexFormat> out;
	for (int i = 0; i < vertices.size(); i++)
	{
		out.push_back(
			VertexFormat(vertices[i], uvs[i], normals[i], tangents[i],  bitangents[i])
		);
	}
	return out;
}

void Mesh::Update()
{
	//glUseProgram(program);
	glm::mat4 transformMatrix = transform->getTransformMatrix();
	glm::mat4 ViewMatrix = Camera::GetViewMatrix();
	glm::mat4 ProjectionMatrix = Camera::GetProjectionMatrix();
	// Send mvp to currently bound shader
	glm::mat4 mv = ViewMatrix * ModelMatrix;
	glm::mat4 mvp = ProjectionMatrix * mv;
	glUniformMatrix4fv(MV_ID, 1, GL_FALSE, &mv[0][0]);
	glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(Trans_ID, 1, GL_FALSE, &transformMatrix[0][0]);

	// Send normal matrix to currently bound shader
	//glm::mat3 NormalMatrix = glm::mat3(glm::transpose(glm::inverse(ModelMatrix)));
	//glUniformMatrix3fv(NormalMatrix_ID, 1, GL_FALSE, &NormalMatrix[0][0]);
}

std::vector<glm::vec3> Mesh::GetPositionVertices()
{
	return vertices;
}

void Mesh::Draw(GLuint program)
{	
	//glUseProgram(program);

	for (int i=0; i < this->textures.size(); ++i)
	{
		TextureType ttype = textures[i].type;
		GLuint texLoc; 
		if (ttype == Texture_Diffuse)
		{
			glUniform1i(glGetUniformLocation(program, "texture_diffuse"), 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		else if (ttype == Texture_Normal)
		{
			glUniform1i(glGetUniformLocation(program, "texture_normal"), 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		else if (ttype == Texture_Specular)
		{
			glUniform1i(glGetUniformLocation(program, "texture_specular"), 2);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		else
		{
		}
	}

	// Add shadow texture
	GLuint shadow_texture_id = Shadow_Manager::GetInstance()->GetShadowMap();
	glUniform1i(glGetUniformLocation(program, "texture_shadow"), 3);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, shadow_texture_id);


	glm::mat4 bias (
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
		);
	glm::mat4 depthMVP = Shadow_Manager::GetInstance()->GetDepthMatrix();
	glm::mat4 depthBiasMVP = bias * depthMVP;

	glUniformMatrix4fv(Depth_ID, 1, GL_FALSE, &depthBiasMVP[0][0]);

	glUniform1f(glGetUniformLocation(program, "Shininess"), shininess);
	glUniform1f(glGetUniformLocation(program, "Strength"), strength);

	// Draw triangles
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, nullptr);
	glBindVertexArray(0);
}

void Mesh::DrawShadow(GLuint shadowProgram)
{
	//glUseProgram(shadowProgram);
	// Send transform array to shadow program
	glm::mat4 transformMatrix = this->transform->getTransformMatrix();
	glUniformMatrix4fv(
		glGetUniformLocation(shadowProgram, "Transform"),
		1, GL_FALSE, &transformMatrix[0][0]);

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
	Trans_ID = glGetUniformLocation(program, "TransformMatrix");
	Depth_ID = glGetUniformLocation(program, "DepthMVP");
	ScaleConst_ID = glGetUniformLocation(program, "ScaleConst");

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

	// Attribute buffer - Tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE,
		sizeof(VertexFormat),
		(void*)(offsetof(VertexFormat, VertexFormat::tangent)));

	// Attribute buffer - Bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE,
		sizeof(VertexFormat),
		(void*)(offsetof(VertexFormat, VertexFormat::bitangent)));

	glBindVertexArray(0);

	//here we assign the values
	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);
}
