#include "Material.h"

#include <iostream>

Material::Material(const Ref<Shader>& shader, const std::vector<BufferElement>& uniformLayout, const std::vector<std::string>& textureLayout)
	: m_Shader(shader), m_UniformBuffer("Material", uniformLayout)
{}
Material::Material(const AssetManager::EntityTemplate& entityTemplate)
	: m_UniformBuffer("Material")
{
	assert(entityTemplate.has("Material"));
	if (!entityTemplate.has("Material"))
	{
		std::cout << "nope2" << std::endl;
	}
	const AssetManager::Asset& asset = entityTemplate.assets.at("Material");

	std::vector<BufferElement> uniformLayout;
	for (auto&& [name, property] : asset.properties)
	{
		if (name == "shaderPath")
		{
			m_Shader = CreateRef<Shader>(property.value);
			continue;
		}

		BufferType bufferType = BufferType::None;

		//TODO: move to global namespace?
		if (property.type == "float") bufferType = BufferType::Float;
		else if (property.type == "float2") bufferType = BufferType::Float2;
		else if (property.type == "float3") bufferType = BufferType::Float3;
		else if (property.type == "float4") bufferType = BufferType::Float4;
		else if (property.type == "int") bufferType = BufferType::Int;
		else if (property.type == "int2") bufferType = BufferType::Int2;
		else if (property.type == "int3") bufferType = BufferType::Int3;
		else if (property.type == "int4") bufferType = BufferType::Int4;
		
		uniformLayout.push_back(BufferElement(name, bufferType));
	}

	m_UniformBuffer.setLayout(uniformLayout);

	for (auto&& [name, property] : asset.properties)
	{

		if (property.type == "float") set(name, std::stof(property.value));
		else if (property.type == "float2") set(name, AssetManager::stof2(property.value));
		else if (property.type == "float3") set(name, AssetManager::stof3(property.value));
		else if (property.type == "float4") set(name, AssetManager::stof4(property.value));
		else if (property.type == "int") set(name, std::stoi(property.value));
		else if (property.type == "int2") set(name, AssetManager::stoi2(property.value));
		else if (property.type == "int3") set(name, AssetManager::stoi3(property.value));
		else if (property.type == "int4") set(name, AssetManager::stoi4(property.value));
	}
}

Ref<Material> Material::create(const Ref<Shader>& shader, const std::vector<BufferElement>& uniforms, const std::vector<std::string>& textures)
{
	return CreateRef<Material>(shader, uniforms, textures);
}
Ref<Material> Material::create(const AssetManager::EntityTemplate& entityTemplate)
{
	return CreateRef<Material>(entityTemplate);
}


void Material::use()
{
	m_Shader->use();
	m_UniformBuffer.bindToShader(m_Shader);
}