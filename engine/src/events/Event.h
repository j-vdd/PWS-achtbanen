#pragma once

#include <functional>
#include <unordered_set>

#include <iostream>

template<typename ...Args>
class Event
{
public:
	using ListenerFn = std::function<void(Args...)>;

	Event() = default;
	~Event()
	{
		//TODO
		for (Listener* listener : m_Listeners)
			listener->setEvent(nullptr);
	}

	class Listener
	{
	public:
		// TODO: copy constructor and assigment operators
		Listener()
			: m_Event(nullptr), m_Callback(nullptr)
		{}
		Listener(ListenerFn callback)
			: m_Event(nullptr), m_Callback(callback)
		{}
		Listener(Event* evnt, ListenerFn callback)
			: m_Event(evnt), m_Callback(callback)
		{
			activate();
		}
		~Listener()
		{
			deactivate();
		}

		Listener(Listener& other)
			: m_Event(other.m_Event), m_Callback(other.m_Callback)
		{
			std::cout << "Copied!" << std::endl;
			activate();
		}
		Listener& operator=(Listener& other)
		{
			m_Event = other.m_Event;
			m_Callback = other.m_Callback;
			activate();
			return *this;
		}
		Listener& operator=(Listener&& other)
		{
			m_Event = other.m_Event;
			m_Callback = other.m_Callback;
			activate();
			return *this;
		}

		void activate()
		{
			if (m_Event)
				m_Event->m_Listeners.insert(this);
		}
		void deactivate()
		{
			if (m_Event)
				m_Event->m_Listeners.erase(this);
		}

		void setEvent(Event* evnt)
		{
			deactivate();
			m_Event = evnt;
			activate();
			
		}
		void setCallback(ListenerFn callback)
		{
			m_Callback = callback;
		}

		void notify(Args... args)
		{
			m_Callback(args...);
		}

	private:
		Event* m_Event; //TODO: shared_ptr?
		ListenerFn m_Callback;
	};

	Listener createListener(ListenerFn callback) {
		return Listener(this, callback);
	}

	// TODO: pass by reference?
	void notify(Args... args)
	{
		for (Listener* listener : m_Listeners)
			listener->notify(args...);
	}

private:
	std::unordered_set<Listener*> m_Listeners;
};