#pragma once

#include <cstdint>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <assert.h>

typedef uint32_t Entity;

class Registry
{
public:
	template<typename... Args>
	Entity create()
	{
		Entity e = genEntityCode();
		m_EntityCodes[e] = 0;

		if constexpr (sizeof...(Args) > 0)
			addComponents<Args...>(e);

		return e;
	}
	void erase(Entity e)
	{
		m_EntityCodes.erase(e);
	}

	template<typename T, typename... Args>
	void addComponents(Entity e)
	{
		addComponent<T>(e);

		if constexpr (sizeof...(Args) > 0) {
			addComponents<Args...>(e);
		}
	}
	template<typename T>
	void addComponent(Entity e)
	{
		m_EntityCodes[e] |= getComponentCode<T>();

		ComponentArray<T>* components = getComponents<T>();
		components->insert(e);
	}
	template<typename T>
	void removeComponent(Entity e)
	{
		ComponentArray<T>* components = getComponents<T>();
		components->erase(e);
	}

	template<typename T>
	bool hasComponent(Entity e)
	{
		return m_EntityCodes[e] & getComponentCode<T>();
	}

	template<typename T>
	T& get(Entity e)
	{
		ComponentArray<T>* componentArray = getComponents<T>();
		assert(componentArray->contains(e));

		return componentArray->get(e);
	}

	template<typename... Args>
	std::vector<Entity> getEntities()
	{
		ComponentCode requiredCode = getMultipleComponentCode<Args...>();

		std::vector<Entity> entities;
		for (auto& [e, code] : m_EntityCodes)
		{
			if ((code & requiredCode) == requiredCode)
				entities.push_back(e);
		}

		return entities;
	}
	template<typename... Args>
	Entity getEntity()
	{
		ComponentCode requiredCode = getMultipleComponentCode<Args...>();

		std::unordered_set<Entity> entities;
		for (auto& [e, code] : m_EntityCodes)
		{
			if ((code & requiredCode) == requiredCode)
				return e;
		}

		return 0;
	}

private:
	typedef uint64_t ComponentCode;

	class IComponentArray
	{
	public:
		virtual void erase(Entity e) = 0;
		virtual bool contains(Entity e) = 0;
	};

	template<typename T>
	class ComponentArray
	{
	public:
		ComponentArray()
			: m_Components()
		{}

		void erase(Entity e) 
		{
			m_Components.erase(e);
		}
		bool contains(Entity e)
		{
			return m_Components.contains(e);
		}
		T& get(Entity e)
		{
			return m_Components.at(e);
		}
		void insert(Entity e)
		{
			//m_Components.emplace(e, {});
			//m_Components.insert({ e, T() }); //TODO
			m_Components[e];// = T();
		}
	private:
		std::unordered_map<Entity, T> m_Components;
	};

	Entity genEntityCode()
	{
		return m_EntityCounter++;
	}
	Entity m_EntityCounter = 1;

	template<typename T>
	bool componentExists()
	{
		return m_ComponentCodes.contains(typeid(T));
	}

	std::unordered_map<std::type_index, IComponentArray*> m_ComponentArrays;

	template<typename T>
	ComponentArray<T>* getComponents()
	{
		const std::type_index index = typeid(T);
		assert(m_ComponentArrays.contains(index));

		return (ComponentArray<T>*)m_ComponentArrays[index];
	}

	template<typename T, typename... Args>
	ComponentCode getMultipleComponentCode()
	{
		ComponentCode code = getComponentCode<T>();
		if constexpr (sizeof...(Args) > 0) {
			code |= getMultipleComponentCode<Args...>();
		}

		return code;
	}


	ComponentCode m_ComponentCounter = 1;
	std::unordered_map<std::type_index, ComponentCode> m_ComponentCodes;

	template<typename T>
	ComponentCode getComponentCode()
	{
		const std::type_index index = typeid(T);
		
		if (!componentExists<T>())
		{
			m_ComponentCodes[index] = m_ComponentCounter;
			m_ComponentCounter *= 2;

			m_ComponentArrays[index] = (IComponentArray*)(new ComponentArray<T>());
		}

		return m_ComponentCodes.at(index);
	}
	
	std::unordered_map<Entity, ComponentCode> m_EntityCodes;
};