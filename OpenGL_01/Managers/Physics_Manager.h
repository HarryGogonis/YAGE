#pragma once
#include "btBulletDynamicsCommon.h"
#include "../Rendering/Util/DebugDrawer.h"

class Physics_Manager
{
public:
	~Physics_Manager();
	static Physics_Manager* GetInstance();
	void Step();
	void DrawDebug();
	void AddRigidBody(btRigidBody*);
	void AddConstraint(btTypedConstraint*);
private:
	Physics_Manager();
	void initWorld();
	void clearLines();

	// Static instance of Physics_Manager because who wants two physics systems?
	static Physics_Manager* m_physics_mgr;
	
	btBroadphaseInterface* broadphase;
	btCollisionDispatcher* dispatcher;
	btConstraintSolver*	solver;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btDiscreteDynamicsWorld* dynamicsWorld;
	btClock* clock;
	DebugDrawer* drawer;
};
