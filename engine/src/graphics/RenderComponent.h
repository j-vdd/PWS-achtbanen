#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Texture2D.h"

#include "Ref.h"

struct RenderComponent
{
	RenderComponent()
		: mesh{}, material{}
	{}
	RenderComponent(const Ref<Mesh>& _mesh, const Ref<Material>& _material)
		: mesh(_mesh), material(_material)
	{}

	void use() const
	{
		material->use();
		mesh->bind();
	}
	void unuse() const
	{
		mesh->unbind();
	}

	Ref<Mesh> mesh;

	Ref<Material> material;
};