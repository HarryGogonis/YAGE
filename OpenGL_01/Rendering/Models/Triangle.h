#pragma once
#include "Model.h"

class Triangle : public Model
{
public:
	Triangle(Transform t, Color c);
	~Triangle();

	void Create();
	virtual void Update() override final;
	virtual void Draw() override final;
	virtual std::vector<VertexFormat> GetVertices() override;
};