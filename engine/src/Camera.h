#pragma once

#include <iostream>

#include "common.h"

#include "events/windowEvents.h"

using namespace math;

struct Camera
{
public:
	Camera(const Vec3& _position = Vec3{ 0 }, const Quatf& _rotation = Quatf(Vec3(0)), float _fov = 1.f, float _aspect = 1.f, float _near = 0.1f, float _far = 1000.0f) :
		position(_position), rotation(_rotation),
		fov(_fov), aspect(_aspect), near(_near), far(_far)
	{}

	const Mat4 projectionMatrix() const { return perspectiveTransform(fov, aspect, near, far); }
	const Mat4 viewMatrix() const { return viewTransform(position, rotation); }

	WindowResizeEvent::Listener& getResizeListener() { return m_ResizeListener; }
	void setResizeEvent(WindowResizeEvent* resizeEvent);

	Vec3 position;
	Quatf rotation;

	float fov, aspect, near, far;

private:
	void resizeCallback(int width, int height) 
	{
		aspect = float(width) / float(height);
	}
	WindowResizeEvent::Listener m_ResizeListener;
};