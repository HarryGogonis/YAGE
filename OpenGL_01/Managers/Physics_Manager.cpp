#include "Physics_Manager.h"
#include <iostream>
#include "../Rendering/Util/DebugDrawer.h"
#include "../Core/Options.h"
Physics_Manager* Physics_Manager::m_physics_mgr = nullptr;

Physics_Manager* Physics_Manager::GetInstance()
{
	if (!m_physics_mgr)
	{
		m_physics_mgr = new Physics_Manager();
	}
	return m_physics_mgr;
}


Physics_Manager::Physics_Manager()
{
	initWorld();
}


Physics_Manager::~Physics_Manager()
{
	int constraintsCount = dynamicsWorld->getNumConstraints();
	for (int i = 0; i != constraintsCount; ++i)
	{
		btTypedConstraint* constraint = dynamicsWorld->getConstraint(i);
		dynamicsWorld->removeConstraint(dynamicsWorld->getConstraint(i));
		delete constraint;
		constraint = nullptr;
	}
	delete dynamicsWorld;
	dynamicsWorld = nullptr;
	delete solver;
	solver = nullptr;
	delete broadphase;
	broadphase = nullptr;
	delete dispatcher;
	dispatcher = nullptr;
	delete collisionConfiguration;
	collisionConfiguration = nullptr;
	delete clock;
	clock = nullptr;
	delete drawer;
	drawer = nullptr;
}

void Physics_Manager::initWorld()
{
	clock = nullptr;
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	broadphase = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -1, 0));

	// Absolute base plane so all RigidBodies can be accounted for even if they phase through the ground
	btCollisionShape* ground = new btStaticPlaneShape(btVector3(0, 1, 0), -15);
	btTransform* transform = new btTransform(btQuaternion(), btVector3(0, 0, 0));
	transform->setIdentity();
	btDefaultMotionState* motionState = new btDefaultMotionState(*transform);
	btRigidBody::btRigidBodyConstructionInfo info(0.f, motionState, ground);
	btRigidBody *body = new btRigidBody(info);
	dynamicsWorld->addRigidBody(body);

	drawer = new DebugDrawer();
	drawer->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
	dynamicsWorld->setDebugDrawer(drawer);
}

void Physics_Manager::Step()
{
		btCollisionObject* diablo = dynamicsWorld->getCollisionObjectArray()[0];
		btRigidBody* realDiablo = btRigidBody::upcast(diablo);
		btTransform trans;
		realDiablo->getMotionState()->getWorldTransform(trans);
	if (!clock)
	{
		clock = new btClock();
	}
	dynamicsWorld->stepSimulation(clock->getTimeSeconds(), 1);
}

void Physics_Manager::AddRigidBody(btRigidBody* body)
{
	dynamicsWorld->addRigidBody(body);
}

void Physics_Manager::AddConstraint(btTypedConstraint* constraint)
{
	dynamicsWorld->addConstraint(constraint, false);
}

void Physics_Manager::DrawDebug()
{
	if (DRAW_WIREFRAMES)
	{
		drawer->clearBuffers();
		dynamicsWorld->debugDrawWorld();
		drawer->render();
	}
}
