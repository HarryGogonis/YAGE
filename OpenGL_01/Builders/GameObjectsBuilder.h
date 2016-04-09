#pragma once
#include "../Managers/Models_Manager.h"

// Everything except OT_NONE and OT_MODEL bit-wise AND with OT_LIGHT for a non-zero result
enum GameObjectType
{
	OT_NONE					= 0,
	OT_MODEL				= 1,
	OT_LIGHT				= 2,
	OT_LIGHT_DIRECTIONAL	= 3,
	OT_LIGHT_AMBIENT		= 6,
	OT_LIGHT_POINT			= 7,
	OT_LIGHT_SPOT			= 10
};

class GameObjectsBuilder
{
public:
	GameObjectsBuilder();
	~GameObjectsBuilder();

	GameObjectsBuilder & addModel(
		const std::string modelPath, 
		const std::string texturePath = std::string());

			GameObjectsBuilder & setPosition(glm::vec3);
			GameObjectsBuilder & setScale(float);
			GameObjectsBuilder & setRotation(float angleX, float angleY, float angleZ);
			// Initializes collision detection with no gravity if mass is '0.f'
			GameObjectsBuilder & addRigidBody(float mass);
			// Limit rotation on Y axis and translation on X and Y axes
			GameObjectsBuilder & lockUpright();

	// All lights
	GameObjectsBuilder & addLight(GameObjectType type);

			GameObjectsBuilder & setColor(glm::vec3 color);
			GameObjectsBuilder & setHalfVector(glm::vec3 halfVector);
			GameObjectsBuilder & setCastsShadows(bool);
			// Only call AFTER color is set
			GameObjectsBuilder & setStrength(float strength);

			// Spotlight and Point Light
			GameObjectsBuilder & setAttenuation(float constant, float linear, float quadratic);

			// Spotlight
			GameObjectsBuilder & setConeDirection(glm::vec3 coneDirection);
			GameObjectsBuilder & setSpotCutoff(float cutoff);
			GameObjectsBuilder & setSpotExponent(float exponent);


	Models_Manager* getResult() const;
private:
	Models_Manager* models;
	IGameObject* current;
	GameObjectType current_type;
};

