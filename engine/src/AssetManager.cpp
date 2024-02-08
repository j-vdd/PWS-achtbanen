#include "AssetManager.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

void AssetManager::loadTemplates(const std::string& relativePath)
{
	const std::string filepath = m_BasePath + relativePath;
	std::ifstream file(filepath);
	assert(file.is_open());

	EntityTemplate* currentTemplate = nullptr;
	Asset* currentAsset = nullptr;

	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream lineStream(line);
		
		std::vector<std::string> keywords;
		std::string token;
		while (lineStream >> token)
			keywords.push_back(token);

		if (keywords.size() == 0)
			continue;

		if (keywords[0] == "Entity")
		{
			const std::string& name = keywords[1];

			m_LoadedTemplates[name] = EntityTemplate();
			currentTemplate = &m_LoadedTemplates[name];
		}
		else if (keywords[0] == "Asset")
		{
			const std::string& type = keywords[1];
			if (type.size() && currentTemplate)
			{
				currentTemplate->assets[type] = Asset();
				currentAsset = &currentTemplate->assets[type];
			}
		}
		else if (currentAsset)
		{
			Property prop;
			prop.type = keywords[0];
			const std::string& name = keywords[1];
			prop.value = "";
			if (prop.type == "path")
			{
				prop.value = m_BasePath + prop.value;
				prop.type = "string";
			}

			for (size_t i = 2; i < keywords.size(); i++)
				prop.value += keywords[i];

			currentAsset->properties[name] = prop;
		}
	}

	file.close();
}

void AssetManager::clearTemplates()
{
	m_LoadedTemplates.clear();
}

Vec2 AssetManager::stof2(const std::string& str)
{
	auto comps = parseToVector(str);
	return Vec2(std::stof(comps[0]), std::stof(comps[1]));
}
Vec3 AssetManager::stof3(const std::string& str)
{
	auto comps = parseToVector(str);
	return Vec3(std::stof(comps[0]), std::stof(comps[1]), std::stof(comps[2]));
}
Vec4 AssetManager::stof4(const std::string& str)
{
	auto comps = parseToVector(str);
	return Vec4(std::stof(comps[0]), std::stof(comps[1]), std::stof(comps[2]), std::stof(comps[3]));
}

IVec2 AssetManager::stoi2(const std::string& str)
{
	auto comps = parseToVector(str);
	return IVec2(std::stoi(comps[0]), std::stoi(comps[1]));
}
IVec3 AssetManager::stoi3(const std::string& str)
{
	auto comps = parseToVector(str);
	return IVec3(std::stoi(comps[0]), std::stoi(comps[1]), std::stoi(comps[2]));
}
IVec4 AssetManager::stoi4(const std::string& str)
{
	auto comps = parseToVector(str);
	return IVec4(std::stoi(comps[0]), std::stoi(comps[1]), std::stoi(comps[2]), std::stoi(comps[3]));
}

void AssetManager::replaceAll(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
}
std::vector<std::string> AssetManager::parseToVector(const std::string& str)
{
	std::vector<std::string> out;

	size_t start = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		char c = str[i];
		if (c == '{' || c == ' ')
			start = i + 1;

		if (c == ',' || c == '}')
		{
			out.push_back(str.substr(start, i - start));
			start = i + 1;
		}
	}

	return out;
}