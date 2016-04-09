#include "GameObjectsBuilder.h"
#include "../Managers/Physics_Manager.h"


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

GameObjectsBuilder & GameObjectsBuilder::setPosition(glm::vec3 pos)
{
	if (current_type == OT_MODEL)
	{
		Scene_Container* model = static_cast<Scene_Container*>(current);
		model->transform.position = pos;
	}
	else if (current_type & OT_LIGHT)
	{
		Light* light = static_cast<Light*>(current);
		light->position = pos;
	}
	return *this;
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

GameObjectsBuilder& GameObjectsBuilder::addRigidBody(float mass)
{
	if (current_type == OT_MODEL)
	{
		Scene_Container* model = static_cast<Scene_Container*>(current);
		model->InitRigidBody(mass);
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

Models_Manager* GameObjectsBuilder::getResult()
{
	return models;
}
