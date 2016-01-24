#pragma once
#include "Model.h"

class Quad :public Model
{
public:
	Quad();
	~Quad();

	void Create();
	virtual void Draw() override final;
	virtual void Update() override final;
	virtual std::vector<VertexFormat> GetVertices() override;
};