#pragma once

#include <string>
#include <unordered_map>

#include "Ref.h"

#include "common.h"

#include "Shader.h"
#include "UniformBuffer.h"
#include "Texture2D.h"

#include "AssetManager.h"

using namespace math;

class Material
{
public:
	//Material(const Ref<Shader>& shader, const Ref<MaterialLayout>& layout);
	Material(const Ref<Shader>& shader, const std::vector<BufferElement>& uniforms, const std::vector<std::string>& textures = {});
	Material(const AssetManager::EntityTemplate& entityTemplate);

	static Ref<Material> create(const Ref<Shader>& shader, const std::vector<BufferElement>& uniforms, const std::vector<std::string>& textures = {});
	static Ref<Material> create(const AssetManager::EntityTemplate& entityTemplate);

	void use();

	void set(const std::string& name, float value) { m_UniformBuffer.set(name, value); }
	void set(const std::string& name, const Vec2& value) { m_UniformBuffer.set(name, value); }
	void set(const std::string& name, const Vec3& value) { m_UniformBuffer.set(name, value); }
	void set(const std::string& name, const Vec4& value) { m_UniformBuffer.set(name, value); }

	void set(const std::string& name, int value) { m_UniformBuffer.set(name, value); }
	void set(const std::string& name, const IVec2& value) { m_UniformBuffer.set(name, value); }
	void set(const std::string& name, const IVec3& value) { m_UniformBuffer.set(name, value); }
	void set(const std::string& name, const IVec4& value) { m_UniformBuffer.set(name, value); }

	void set(const std::string& name, bool value) { m_UniformBuffer.set(name, value); }

	void set(const std::string& name, Ref<Texture2D>& texture);

	const Ref<Shader>& getShader() const { return m_Shader; }

private:
	UniformBuffer m_UniformBuffer;
	//std::vector<Texture2D> m_Textures;

	Ref<Shader> m_Shader;
};