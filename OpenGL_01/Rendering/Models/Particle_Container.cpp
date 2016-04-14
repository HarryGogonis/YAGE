#include "Particle_Container.h"
#include "../Util/Camera.h"
#include "glm/gtx/norm.hpp"
#include <algorithm>
#include "../../Managers/Shader_Factory.h"
#include <SOIL.h>

int lastTime;
double delta;

int Particle_Container::instanceCount = 0;

Particle_Container::Particle_Container(Transform t, const std::string& texturePath, bool enable,
	int max_particles, int particle_rate, float particle_max_life)
{
	MaxParticles = max_particles;
	ParticleCount = 0;
	LastUsedParticle = 0;
	spawn_rate = particle_rate;
	max_life = particle_max_life;
	isEnabled = enable;
	particles = std::vector<Particle>(max_particles);
	position_data = new GLfloat[max_particles * 4];
	color_data = new GLubyte[max_particles * 4];

	Shader_Factory* shader_manager = Shader_Factory::GetInstance();
	SetProgram(shader_manager->CreateProgram(
		"particleShader" + instanceCount++,
		"Shaders\\ParticleVertexShader.glsl",
		"Shaders\\ParticleFragmentShader.glsl"));

	GLuint textureID = SOIL_load_OGL_texture(
		texturePath.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y);
	SetTexture("particleTexture", Texture_Diffuse, textureID);

	MVP_ID = glGetUniformLocation(program, "MVP");
	Texture_ID = glGetUniformLocation(program, "particle_texture");
	CameraUp_ID = glGetUniformLocation(program, "CameraUp");
	CameraRight_ID = glGetUniformLocation(program, "CameraRight");

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
	};

	for (int i = 0; i < MaxParticles; i++)
	{
		particles[i].life = -1.0f;
		particles[i].cameradistance = -1.0f;
	}

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//  VBO containing positions and size of particles
	glGenBuffers(1, &position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
	// Init empty buffer, updated at each frame
	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), nullptr, GL_STREAM_DRAW);


	// VBO containing colors of particles
	glGenBuffers(1, &color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
	// Init empty buffer, updated at each frame
	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), nullptr, GL_STREAM_DRAW);

	lastTime = glutGet(GLUT_ELAPSED_TIME);
}

Particle_Container::~Particle_Container()
{
	delete[] position_data;
	delete[] color_data;
}

void Particle_Container::Draw(GLuint p)
{
	// TODO
	Draw();
}

void Particle_Container::Draw()
{
	glUseProgram(program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(Texture_ID, 0);

	glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), nullptr, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, ParticleCount * sizeof(GLfloat) * 4, position_data);

	glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), nullptr, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, ParticleCount * sizeof(GLubyte) * 4, color_data);

	// 1st attribute array: vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	// 2nd attribute array: positions
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

	// 3rd attribute array: colors
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, nullptr);

	glVertexAttribDivisor(0, 0);
	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(2, 2);

	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, ParticleCount);
}

void Particle_Container::Update()
{
	glUseProgram(program);
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	delta = double(currentTime - lastTime) / 1000.0;
	lastTime = currentTime;

	glm::mat4 ViewMatrix = Camera::GetViewMatrix();
	glm::mat4 ProjectionMatrix = Camera::GetProjectionMatrix();
	glm::mat4 mvp = ProjectionMatrix * ViewMatrix;

	glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, &mvp[0][0]); //TODO init MVP_ID
	glUniform3f(CameraRight_ID, ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]);
	glUniform3f(CameraUp_ID, ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]);
	
	int newparticles = int(delta * double(spawn_rate));
	if (delta > 0.016f)
		newparticles = int(0.016f * double(spawn_rate));

	// Add new particles
	AddNewParticles(newparticles);

	// Simulate all particles
	SimulateParticles();

	// Sort all particles
	SortParticles();
}

void Particle_Container::Destroy()
{
	// TODO implement
}

void Particle_Container::SetTexture(const std::string&, const TextureType& type, const GLuint& id)
{
	if (type == Texture_Diffuse)
	{
		texture = id;
	}
	else
	{
		
	}
}

const GLuint Particle_Container::GetTexture(const std::string&) const
{
	return texture;
}

void Particle_Container::setMaxParticles(int n)
{
	this->MaxParticles = n;
}

void Particle_Container::setSpawnRate(int rate)
{
	this->spawn_rate = rate;
}

void Particle_Container::setMaxLife(float life)
{
	this->max_life = life;
}

void Particle_Container::AddNewParticles(int newparticles)
{
	for (int i = 0; i < newparticles; i++)
	{
		int pIndex = FindUnusedParticle();
		particles[pIndex].life = max_life; //TODO randomize between (min_life, max_life)
		particles[pIndex].pos = t.position;
		// TODO don't hardcode a lot of these values
		float spread = 1.5f;

		glm::vec3 main_dir = glm::vec3(0.0f, 10.0f, 0.0f);

		// TODO better random direction
		glm::vec3 random_dir = glm::vec3(
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f
			);

		particles[pIndex].speed = main_dir + random_dir * spread;

		// TODO better random color
		particles[pIndex].r = rand() % 256;
		particles[pIndex].g = rand() % 256;
		particles[pIndex].b = rand() % 256;
		particles[pIndex].a = (rand() % 256) / 3;

		// TODO better random size
		particles[pIndex].size = (rand() % 1000) / 2000.0f + 0.1f;
	}
}

void Particle_Container::SimulateParticles()
{
	ParticleCount = 0;

	for (int i = 0; i < MaxParticles; i++)
	{
		Particle& p = particles[i];

		if (p.life > 0.0f)
		{
			// Decrease life
			p.life -= delta;
			if (p.life > 0.0f)
			{
				// Simulate simple gravity physics 
				// TODO replace w/ bullet
				p.speed += glm::vec3(0.0f, -9.81f, 0.0f) * float(delta) * 0.5f;
				p.pos += p.speed * float(delta);
				p.cameradistance = glm::length2(p.pos - Camera::GetEyeDirection());
				
				// Fill the GPU buffer
				position_data[4 * ParticleCount + 0] = p.pos.x;
				position_data[4 * ParticleCount + 1] = p.pos.y;
				position_data[4 * ParticleCount + 2] = p.pos.z;
				position_data[4 * ParticleCount + 3] = p.size;

				color_data[4 * ParticleCount + 0] = p.r;
				color_data[4 * ParticleCount + 1] = p.g;
				color_data[4 * ParticleCount + 2] = p.b;
				color_data[4 * ParticleCount + 3] = p.a;
			} else
			{
				p.cameradistance = -1.0f;
			}
			ParticleCount++;
		}
	}
}

void Particle_Container::SortParticles()
{
	std::sort(particles.begin(), particles.end());
}

int Particle_Container::FindUnusedParticle()
{
	for (int i = LastUsedParticle; i < MaxParticles; i++)
	{
		if (particles[i].life < 0)
		{
			LastUsedParticle = i;
			return i;
		}
	}
	
	for (int i = 0; i < MaxParticles; i++)
	{
		if (particles[i].life < 0)
		{
			LastUsedParticle = i;
			return i;
		}
	}

	return 0; // all particles are taken
}
