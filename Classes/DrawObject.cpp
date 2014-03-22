#include "DrawObject.h"

// on "init" you need to initialize your instance
bool DrawObject::init()
{
    return true;
}

void DrawObject::setOnDraw(const function<void()>& onDraw)
{
	m_on_draw = onDraw;
}

void DrawObject::draw()
{
	m_on_draw();
}