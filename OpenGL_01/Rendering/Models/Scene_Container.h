#pragma once
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include "btBulletDynamicsCommon.h"
#include "Mesh.h"

class Scene_Container : public IGameObject
{
public:
	Scene_Container(const std::string&, Transform);
	Scene_Container(const Scene_Container*&, Transform);

	~Scene_Container();

	// Draw function so that we are sure that the Scene_Container uses its own program
	void Draw();
	void Draw(GLuint) override;
	void DrawShadow();
	void DrawShadow(GLuint) override;
	void Update() override;
	void Destroy() override;

	void SetProgram(GLuint) override;
	void SetShadowProgram(GLuint) override;

	btRigidBody* getRigidBody();
	virtual void InitRigidBody(btScalar mass);
	const std::vector<Mesh*> GetMeshes() const;

	void SetTexture(const std::string&,const TextureType&, const GLuint&) override;
	const GLuint GetTexture(const std::string&) const override;

	Transform transform;
private:
	std::vector<Mesh*> meshes;
	const aiScene *scene;
	btCollisionObject *collisionBody; 
	btConvexHullShape* collisionShape;
	btRigidBody* rigidBody;
	bool isDynamic;
	int texture_id = 0;

	void addMeshWithMat(const aiMesh*, const aiMaterial*);
	void CreateCollisionShape();
};

