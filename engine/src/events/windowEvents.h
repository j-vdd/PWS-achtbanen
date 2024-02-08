#pragma once

#include "Event.h"

//width, height
using WindowResizeEvent = Event<int, int>;

//mouse
using MouseMoveEvent = Event<float, float>; //x, y
using MousePressEvent = Event<int>; //button