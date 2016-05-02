#pragma once
#include "btBulletDynamicsCommon.h"

// Lots of forward declarations to make this work...
class Scene_Container;
struct CharacterContainer;
class DebugDrawer;

class Physics_Manager
{
public:
	~Physics_Manager();
	static Physics_Manager* GetInstance();
	void setCharacter(Scene_Container* actor);
	void Step();
	void DrawDebug();
	void AddRigidBody(btRigidBody*);
	void AddConstraint(btTypedConstraint*);
	btRigidBody* getActorBody();
	CharacterContainer* getCharacter();
private:
	Physics_Manager();
	void initWorld();

	// Static instance of Physics_Manager because who wants two physics systems?
	static Physics_Manager* m_physics_mgr;
	
	btBroadphaseInterface* broadphase = nullptr;
	btCollisionDispatcher* dispatcher = nullptr;
	btConstraintSolver*	solver = nullptr;
	btDefaultCollisionConfiguration* collisionConfiguration = nullptr;
	btDiscreteDynamicsWorld* dynamicsWorld = nullptr;
	btClock* clock = nullptr;
	DebugDrawer* drawer = nullptr;
	CharacterContainer* charContainer = nullptr;

	float gravity = -9.8f;
	bool leftPressed, rightPressed;
};
