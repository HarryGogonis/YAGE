#include "../Rendering/Util/Camera.h"
#include "Physics_Manager.h"
#include "../Rendering/Util/DebugDrawer.h"
#include "../Core/Options.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "BulletDynamics/Character/btKinematicCharacterController.h"

#include <GL/freeglut.h>

struct CharacterContainer
{
	btPairCachingGhostObject* ghost;
	btKinematicCharacterController* controller;
	Scene_Container* actor;
	btGhostPairCallback* callback;
	bool leftPressed, rightPressed;

	CharacterContainer(Scene_Container* actor)
	{
		this->actor = actor;
		ghost = new btPairCachingGhostObject();
		ghost->setCollisionShape(actor->getRigidBody()->getCollisionShape());
		btTransform t = actor->getRigidBody()->getWorldTransform();
		ghost->setWorldTransform(t);
		ghost->setCollisionFlags(ghost->getCollisionFlags()
			| btCollisionObject::CF_CHARACTER_OBJECT);
		actor->getRigidBody()->setCollisionFlags(actor->getRigidBody()->getCollisionFlags()
			| btCollisionObject::CF_NO_CONTACT_RESPONSE);
		actor->getRigidBody()->setGravity(btVector3(0.f, 0.f, 0.f));
		controller = new btKinematicCharacterController(
			ghost,
			static_cast<btConvexShape*>(actor->getRigidBody()->getCollisionShape()),
			0.3f);
		controller->setJumpSpeed(15.f);
		callback = new btGhostPairCallback();
	}

	~CharacterContainer()
	{
		delete callback;
		callback = nullptr;
		delete controller;
		controller = nullptr;
		delete ghost;
		ghost = nullptr;
	}
};

void onKeyPressed(const unsigned char key, int x, int y)
{
	Physics_Manager* physics_mgr = Physics_Manager::GetInstance();
	btRigidBody* actor = physics_mgr->getActorBody();
	CharacterContainer* charContainer = physics_mgr->getCharacter();
	if (charContainer)
	{
		btVector3 prev = actor->getLinearVelocity();
		btKinematicCharacterController* controller = charContainer->controller;
		switch (key)
		{
		case 'd':
			charContainer->rightPressed = true;
			controller->setWalkDirection(btVector3(.05f, 0.f, 0.f));
			break;
		case 'a':
			charContainer->leftPressed = true;
			controller->setWalkDirection(btVector3(-.05f, 0.f, 0.f));
			break;
		case 'w':
			controller->jump();
			break;
		default:
			break;
		}
	}
	else
	{
		Camera::onKeyPressed(key);
	}
}

void onKeyRelease(unsigned char key, int x, int y)
{
	Physics_Manager* physics_mgr = Physics_Manager::GetInstance();
	btRigidBody* actor = physics_mgr->getActorBody();
	CharacterContainer* charContainer = physics_mgr->getCharacter();
	if (key == 'a')
		charContainer->leftPressed = false;
	else if (key == 'd')
		charContainer->rightPressed = false;
	if (charContainer)
	{
		btVector3 walk = btVector3(0.f, 0.f, 0.f);
		if (charContainer->leftPressed)
			walk.setX(-0.2f);
		else if (charContainer->rightPressed)
			walk.setX(0.2f);
		btKinematicCharacterController* controller = charContainer->controller;
		controller->setWalkDirection(btVector3(0.f, 0.f, 0.f));
	}
}

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
	if (charContainer)
	{
		delete charContainer;
		charContainer = nullptr;
	}
}

void Physics_Manager::initWorld()
{
	glutKeyboardFunc(onKeyPressed);
	glutKeyboardUpFunc(onKeyRelease);
	clock = nullptr;
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	broadphase = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0.f, gravity, 0.f));

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

void Physics_Manager::setCharacter(Scene_Container* actor)
{
	charContainer = new CharacterContainer(actor);
	charContainer->controller->setGravity(abs(gravity));
	dynamicsWorld->addAction(charContainer->controller);
	dynamicsWorld->addCollisionObject(
		charContainer->ghost,
		btBroadphaseProxy::CharacterFilter,
		btBroadphaseProxy::StaticFilter | btBroadphaseProxy::DefaultFilter);
	dynamicsWorld->getPairCache()->setInternalGhostPairCallback(charContainer->callback);
}

void Physics_Manager::Step()
{
	if (!clock)
	{
		clock = new btClock();
	}
	float secs = clock->getTimeSeconds();
	getActorBody()->setWorldTransform(charContainer->ghost->getWorldTransform());
	dynamicsWorld->stepSimulation(secs);
	Scene_Container* player_model = charContainer ?
		static_cast<Scene_Container*>(charContainer->actor) :
		nullptr;
	Camera::ComputeMatrices(player_model);
}

void Physics_Manager::AddRigidBody(btRigidBody* body)
{
	dynamicsWorld->addRigidBody(body);
}

void Physics_Manager::AddConstraint(btTypedConstraint* constraint)
{
	dynamicsWorld->addConstraint(constraint, false);
}

btRigidBody* Physics_Manager::getActorBody()
{
	if (charContainer)
	{
		return charContainer->actor->getRigidBody();
	}
	return nullptr;
}

CharacterContainer * Physics_Manager::getCharacter()
{
	return charContainer;
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
