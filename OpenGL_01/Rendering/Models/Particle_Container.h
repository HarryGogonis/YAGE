#pragma once
#include "../IGameObject.h"
#include "GL/glew.h"
#include <vector>

class Particle_Container: public IGameObject
{
public:
	Particle_Container(Transform t, const std::string& texturePath, bool enable = true,
		int max_particles = 10000, int particle_rate = 1000, float particle_max_life = 5);
	~Particle_Container();

	void Draw();
	void Draw(GLuint) override;
	void DrawShadow() {}; // Don't draw shadows
	void DrawShadow(GLuint) override {};
	void Update() override;
	void Destroy() override;

	void SetTexture(const std::string&, const TextureType&, const GLuint&) override;
	const GLuint GetTexture(const std::string&) const override;

	void setMaxParticles(int);
	void setSpawnRate(int);
	void setMaxLife(float);

private:
	static int instanceCount;
	int MaxParticles, ParticleCount, LastUsedParticle;
	Transform t;

	int spawn_rate;
	float max_life;
	bool isEnabled;

	struct Particle
	{
		glm::vec3 pos, speed;
		unsigned char r, g, b, a;
		float size, angle, weight;
		float life;				// Remaining life of the particle. if < 0 : dead and unused.
		float cameradistance;	// squared distance to camera
		
		bool operator<(const Particle& that) const {
			// sort in reverse order
			return this->cameradistance > that.cameradistance;
		}
	};

	std::vector<Particle> particles;
	GLfloat* position_data;
	GLubyte* color_data;

	GLuint vertex_buffer, position_buffer, color_buffer;
	GLuint MVP_ID, Texture_ID, CameraUp_ID, CameraRight_ID;
	GLuint texture;

	int FindUnusedParticle();
	void AddNewParticles(int);
	void SimulateParticles();
	void SortParticles();
};
