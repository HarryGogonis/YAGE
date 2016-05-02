#include "GameObjectsBuilder.h"
#include "../Managers/Physics_Manager.h"
#include <SOIL.h>
#include "../Rendering/Util/TextureLoader.h"


GameObjectsBuilder::GameObjectsBuilder()
{
	models = new Models_Manager();
	current_type = OT_NONE;
}


GameObjectsBuilder::~GameObjectsBuilder()
{
}

GameObjectsBuilder & GameObjectsBuilder::addModel(const std::string modelPath, const std::string texturePath)
{
	current_type = OT_MODEL;
	current = models->CreateModel(modelPath, Transform(), texturePath);
	return *this;
}

GameObjectsBuilder& GameObjectsBuilder::copyModel()
{
	current_type = OT_MODEL;
	const Scene_Container* model = static_cast<Scene_Container*>(current);
	current = models->CreateModel(model, Transform());
	return *this;
}

GameObjectsBuilder & GameObjectsBuilder::setPosition(glm::vec3 pos)
{
	if (current_type == OT_MODEL)
	{
		Scene_Container* model = static_cast<Scene_Container*>(current);
		model->transform.position = pos;
	}
	else if (current_type == OT_PARTICLE)
	{
		Particle_Container* particle = static_cast<Particle_Container*>(current);
		particle->transform.position = pos;
	}
	else if (current_type & OT_LIGHT)
	{
		Light* light = static_cast<Light*>(current);
		light->position = pos;
	}
	return *this;
}

GameObjectsBuilder& GameObjectsBuilder::setPosition(float x, float y, float z)
{
	return setPosition(glm::vec3(x, y, z));
}

GameObjectsBuilder & GameObjectsBuilder::setScale(float scale)
{
	if (current_type == OT_MODEL)
	{
		Scene_Container* model = static_cast<Scene_Container*>(current);
		model->transform.scale = scale;
	}
	return *this;
}

GameObjectsBuilder & GameObjectsBuilder::setRotation(float angleX, float angleY, float angleZ)
{
	if (current_type == OT_MODEL)
	{
		Scene_Container* model = static_cast<Scene_Container*>(current);
		model->transform.RotateX(angleX);
		model->transform.RotateY(angleY);
		model->transform.RotateZ(angleZ);
	}
	return *this;
}

GameObjectsBuilder& GameObjectsBuilder::setDiffuse(const std::string& path)
{
	if (current_type == OT_MODEL)
	{
		Scene_Container* model = static_cast<Scene_Container*>(current);
		model->SetTexture(path, Texture_Diffuse, TextureLoader::LoadTexture(path));
	}
	return *this;
}

GameObjectsBuilder& GameObjectsBuilder::setNormal(const std::string& path)
{
	if (current_type == OT_MODEL)
	{
		Scene_Container* model = static_cast<Scene_Container*>(current);
		model->SetTexture(path, Texture_Normal, TextureLoader::LoadTexture(path));
	}
	return *this;
}

GameObjectsBuilder& GameObjectsBuilder::setSpecular(const std::string& path)
{
	if (current_type == OT_MODEL)
	{
		Scene_Container* model = static_cast<Scene_Container*>(current);
		model->SetTexture(path, Texture_Specular, TextureLoader::LoadTexture(path));
	}
	return *this;
}

GameObjectsBuilder & GameObjectsBuilder::setDynamic()
{
	if (current_type == OT_MODEL)
	{
		Scene_Container* model = static_cast<Scene_Container*>(current);
		btRigidBody* model_body = model->getRigidBody();
		if (model_body)
		{
			model_body->setActivationState(DISABLE_DEACTIVATION);
		}
	}
	return *this;
}

GameObjectsBuilder& GameObjectsBuilder::addRigidBody(float mass)
{
	if (current_type == OT_MODEL)
	{
		Scene_Container* model = static_cast<Scene_Container*>(current);
		model->InitRigidBody(mass);
	}
	return *this;
}

GameObjectsBuilder & GameObjectsBuilder::controlAsPlayer()
{
	if (current_type == OT_MODEL)
	{
		Physics_Manager::GetInstance()->setCharacter(static_cast<Scene_Container*>(current));
	}
	return *this;
}

GameObjectsBuilder & GameObjectsBuilder::lockUpright()
{
	if (current_type == OT_MODEL)
	{
		Scene_Container* model = static_cast<Scene_Container*>(current);
		btRigidBody* current_body = model->getRigidBody();
		current_body->setLinearFactor(btVector3(1.f, 1.f, 0.f));
		current_body->setAngularFactor(btVector3(0.f, 1.f, 0.f));
	}
	return *this;
}

GameObjectsBuilder& GameObjectsBuilder::addParticleSystem(const std::string& texturePath)
{
	current_type = OT_PARTICLE;
	current = models->CreateParticleSystem(Transform(), texturePath);
	return *this;
}

GameObjectsBuilder& GameObjectsBuilder::setParticleCount(int n)
{
	if (current_type == OT_PARTICLE)
	{
		Particle_Container* particle = static_cast<Particle_Container*>(current);
		particle->setMaxParticles(n);
	}
	return *this;
}

GameObjectsBuilder& GameObjectsBuilder::setParticleSpawnRate(int rate)
{
	if (current_type == OT_PARTICLE)
	{
		Particle_Container* particle = static_cast<Particle_Container*>(current);
		particle->setSpawnRate(rate);
	}
	return *this;
}

GameObjectsBuilder& GameObjectsBuilder::setParticleLife(float seconds)
{
	if (current_type == OT_PARTICLE)
	{
		Particle_Container* particle = static_cast<Particle_Container*>(current);
		particle->setMaxLife(seconds);
	}
	return *this;
}

GameObjectsBuilder & GameObjectsBuilder::addLight(GameObjectType type)
{
	if (type & OT_LIGHT)
	{
		Light* light;
		current_type = type;
		switch (current_type)
		{
		case OT_LIGHT_AMBIENT:
			light = new AmbientLight(glm::vec3(0.f, 0.f, 0.f));
			break;
		case OT_LIGHT_DIRECTIONAL:
			light = new DirectionalLight(
				glm::vec3(0.f, 0.f, 0.f),
				glm::vec3(0.f, 0.f, 0.f),
				glm::vec3(0.f, 0.f, 0.f));
			break;
		case OT_LIGHT_POINT:
			light = new PointLight(
				glm::vec3(0.f, 0.f, 0.f),
				glm::vec3(0.f, 0.f, 0.f));
			break;
		case OT_LIGHT_SPOT:
			light = new SpotLight(
				glm::vec3(0.f, 0.f, 0.f),
				glm::vec3(0.f, 0.f, 0.f),
				glm::vec3(0.f, 0.f, 0.f));
			break;
		default:
			return *this;
		}
		current = light;
		models->addLight(light);
	}
	return *this;
}

GameObjectsBuilder & GameObjectsBuilder::setColor(glm::vec3 color)
{
	if (current_type & OT_LIGHT)
	{
		Light* light = static_cast<Light*>(current);
		light->color = color;
	}
	return *this;
}

GameObjectsBuilder & GameObjectsBuilder::setHalfVector(glm::vec3 halfVector)
{
	if (current_type & OT_LIGHT)
	{
		Light* light = static_cast<Light*>(current);
		light->halfVector = halfVector;
	}
	return *this;
}

GameObjectsBuilder& GameObjectsBuilder::setCastsShadows(bool castsShadow)
{
	if (current_type & OT_LIGHT)
	{
		Light* light = static_cast<Light*>(current);
		if (castsShadow)
			light->EnableShadows();
		else
			light->DisableShadows();
	}
	return *this;
}

GameObjectsBuilder & GameObjectsBuilder::setStrength(float strength)
{
	if (current_type & OT_LIGHT)
	{
		Light* light = static_cast<Light*>(current);
		light->color *= strength;
	}
	return *this;
}

GameObjectsBuilder & GameObjectsBuilder::setAttenuation(float constant, float linear, float quadratic)
{
	if (current_type == OT_LIGHT_POINT || current_type == OT_LIGHT_SPOT)
	{
		Light* light = static_cast<Light*>(current);
		light->SetAttenuation(constant, linear, quadratic);
	}
	return *this;
}

GameObjectsBuilder & GameObjectsBuilder::setConeDirection(glm::vec3 coneDirection)
{
	if (current_type == OT_LIGHT_SPOT)
	{
		Light* light = static_cast<Light*>(current);
		light->coneDirection = coneDirection;
	}
	return *this;
}

GameObjectsBuilder & GameObjectsBuilder::setSpotCutoff(float cutoff)
{
	if (current_type == OT_LIGHT_SPOT)
	{
		Light* light = static_cast<Light*>(current);
		light->spotCosCutoff = cutoff;
	}
	return *this;
}

GameObjectsBuilder & GameObjectsBuilder::setSpotExponent(float exponent)
{
	if (current_type == OT_LIGHT_SPOT)
	{
		Light* light = static_cast<Light*>(current);
		light->spotExponent = exponent;
	}
	return *this;
}

Models_Manager* GameObjectsBuilder::getResult() const
{
	return models;
}
