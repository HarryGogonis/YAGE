#include "Scene_Container.h"
#include "BulletCollision/CollisionShapes/btShapeHull.h"
#include "../../Managers/Physics_Manager.h"

Scene_Container::Scene_Container(const std::string &path, Transform transform)
{
	Assimp::Importer importer;

	this->transform = transform;
	scene = importer.ReadFile(path,
		aiProcess_CalcTangentSpace		|
		aiProcess_Triangulate			|
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType			|
		aiProcess_GenSmoothNormals);

	if (!scene)
	{
		perror(importer.GetErrorString());
		return;
	}

	for (int i = 0; i != scene->mNumMeshes; ++i)
	{
		aiMesh *mesh = scene->mMeshes[i];
		if (scene->mNumMaterials)
		{
			addMeshWithMat(mesh, scene->mMaterials[mesh->mMaterialIndex]);
		}
		else
		{
			addMeshWithMat(mesh, nullptr);
		}
	}
	rigidBody = nullptr;
}

Scene_Container::Scene_Container(const Scene_Container*& other, Transform t)
{
	this->transform = t;
	const std::vector<Mesh*> old_meshes = other->GetMeshes();
	
	for (auto old_mesh : old_meshes)
	{
		meshes.push_back(new Mesh(old_mesh, &transform));
	}
	rigidBody = nullptr;
}


Scene_Container::~Scene_Container()
{
	for (int i = 0; i != meshes.size(); ++i)
	{
		delete meshes[i];
	}
	if (rigidBody)
	{
		delete rigidBody->getMotionState();
		delete collisionShape;
		collisionShape = nullptr;

		delete rigidBody;
		rigidBody = nullptr;
	}
}

void Scene_Container::Destroy()
{}

void Scene_Container::SetProgram(GLuint program)
{
	this->program = program;
	for (int i = 0; i != meshes.size(); ++i)
	{
		meshes[i]->SetProgram(program);
		meshes[i]->Create();
	}
}

void Scene_Container::SetShadowProgram(GLuint program)
{
	this->shadowProgram = program;
	for (int i = 0; i != meshes.size(); ++i)
	{
		meshes[i]->SetShadowProgram(program); // ?? do we really need to do this?
	}
}

btRigidBody * Scene_Container::getRigidBody()
{
	return rigidBody;
}

/**
  * Scene_Container owns this method because I, Dylan, have made an executive decision to make lights bound to
  * the laws of physics impossible; I see no point for it (except for flashlights maybe). Our lights will be static, 
  * so the initialization of rigid bodies can be the sole responsibility of the Scene_Container, because it knows
  * about all of its own vertices.
  *
  * TODO:	Support more than just Convex Hull Shape for collision detection; Triangle Mesh Shape might be more
  *			appropriate for static game objects.
 **/
void Scene_Container::InitRigidBody(btScalar mass)
{
	// Create the collision shape
	CreateCollisionShape();
	btVector3 localInertia(0, 0, 0);
	isDynamic = (mass != 0.f);
	if (isDynamic)
		collisionShape->calculateLocalInertia(mass, localInertia);
	btTransform* transform = new btTransform(
		btQuaternion(this->transform.rotation.x, 
			this->transform.rotation.y, 
			this->transform.rotation.z, 
			this->transform.rotation.w),
		btVector3(this->transform.position.x, 
			this->transform.position.y, 
			this->transform.position.z));
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
		mass,
		new btDefaultMotionState(*transform),
		collisionShape,
		localInertia);
	rigidBody = new btRigidBody(rigidBodyCI);
	rigidBody->setUserPointer(this);
	Physics_Manager::GetInstance()->AddRigidBody(rigidBody);
}

const std::vector<Mesh*> Scene_Container::GetMeshes() const
{
	return meshes;
}

/**
  * This is an extremely expensive operation that would not be necessary if it weren't for maintaining the compatibility
  * of third party libraries (bullet physics in this case, but the same can be seen with assimp). Fortunately, it only
  * needs to be calculated on import
 **/
void Scene_Container::CreateCollisionShape()
{
	// First, we create the complicated convex hull
	collisionShape = new btConvexHullShape();
	std::vector<glm::vec3> origVertices;
	for (int i = 0; i != meshes.size(); ++i)
	{
		origVertices = meshes[i]->GetPositionVertices();
		for (int j = 0; j != origVertices.size(); ++j)
		{
			// Convert and place in new array
			collisionShape->addPoint(btVector3(origVertices[j].x, origVertices[j].y, origVertices[j].z), false);
		}
	}
	// Now we create a much more rough approximation for the collision detection using btShapeHull
	btShapeHull* hull = new btShapeHull(collisionShape);
	btScalar margin = collisionShape->getMargin();
	hull->buildHull(margin);
	btConvexHullShape* simpleShape = new btConvexHullShape();
	for (int i = 0; i != hull->numVertices(); ++i)
	{
		simpleShape->addPoint(hull->getVertexPointer()[i], false);
	}
	simpleShape->recalcLocalAabb();
	delete collisionShape;
	delete hull;
	collisionShape = simpleShape;
	collisionShape->setLocalScaling(btVector3(transform.scale, transform.scale, transform.scale));
	simpleShape->recalcLocalAabb();
}

void Scene_Container::SetTexture(const std::string& textureName, const TextureType& textureType, const GLuint& id)
{
	for (int i = 0; i != meshes.size(); ++i)
	{
		meshes[i]->SetTexture(textureName, textureType, id);
	}
}

const GLuint Scene_Container::GetTexture(const std::string &name) const
{
	GLuint retval = 0;
	Texture *t = nullptr;
	for (int i = 0; i != meshes.size(); ++i)
	{
		retval = meshes[i]->GetTexture(name);
		if (retval)
			return retval;
	}
	std::cout << "ERROR: Scene_Container cannot find texture" << std::endl;
	return retval;
}

void Scene_Container::Draw()
{
	Draw(program);
}

void Scene_Container::DrawShadow()
{
	DrawShadow(shadowProgram);
}

void Scene_Container::Draw(GLuint program)
{
	if (rigidBody && isDynamic)
	{
		btTransform trans;
		rigidBody->getMotionState()->getWorldTransform(trans);
		transform = trans;
	}
	for (int i = 0; i != meshes.size(); ++i)
	{
		meshes[i]->Draw(program);
	}
}

void Scene_Container::DrawShadow(GLuint program)
{
	for (int i = 0; i != meshes.size(); ++i)
	{
		meshes[i]->DrawShadow(program);
	}
}

void Scene_Container::Update()
{
	for (int i = 0; i != meshes.size(); ++i)
	{
		meshes[i]->Update();
	}
}

void Scene_Container::addMeshWithMat(const aiMesh* ai_mesh, const aiMaterial* ai_mat)
{
	Mesh *mesh = new Mesh(ai_mesh, ai_mat, &transform);
	meshes.push_back(mesh);
}

