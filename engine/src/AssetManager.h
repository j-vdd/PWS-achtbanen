#pragma once

#include <string>
#include <unordered_map>
#include <map>
#include <iostream>

#include "ecs/Registry.h"

#include "common.h"

using namespace math;

class AssetManager
{
public:
	struct Property
	{
		std::string type;
		std::string value;
	};
	struct Asset
	{
		std::map<std::string, Property> properties;
	};
	struct EntityTemplate
	{
		inline bool has(const std::string& assetType) const
		{
			return assets.contains(assetType);
		}

		std::unordered_map<std::string, Asset> assets;
	};

	AssetManager(const std::string& basePath) 
		: m_BasePath(basePath)
	{}

	void loadTemplates(const std::string& relativePath);
	void clearTemplates();

	const EntityTemplate& getEntityTemplate(const std::string& name) const 
	{
		if (!m_LoadedTemplates.contains(name))
		{
			std::cout << name << std::endl;
		}
		return m_LoadedTemplates.at(name); 
	}

	static Vec2 stof2(const std::string& str);
	static Vec3 stof3(const std::string& str);
	static Vec4 stof4(const std::string& str);
	static IVec2 stoi2(const std::string& str);
	static IVec3 stoi3(const std::string& str);
	static IVec4 stoi4(const std::string& str);

private:
	static void replaceAll(std::string& str, const std::string& from, const std::string& to);
	static std::vector<std::string> parseToVector(const std::string& str);

	std::unordered_map<std::string, EntityTemplate> m_LoadedTemplates;
	std::string m_BasePath;
};