#include "Camera.h"

void Camera::setResizeEvent(WindowResizeEvent* resizeEvent)
{
	m_ResizeListener = WindowResizeEvent::Listener(resizeEvent, std::bind(&Camera::resizeCallback, this, std::placeholders::_1, std::placeholders::_2));
}