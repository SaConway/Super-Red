#pragma once
#include "AnimatedObject.h"
#include "BodyObject.h"
#include <SFML/Graphics.hpp>

//-----------------------------------------------------------------------------

class MovingObject :public AnimatedObject, public BodyObject
{
public:
	MovingObject(const Texture &, Vector2f &, Vector2i &, Vector2i &);
	virtual ~MovingObject() {};
	virtual void move() = 0;
	virtual void animate() = 0;
	virtual void setStartPos() = 0;
	virtual void draw(RenderWindow & window) const { window.draw(m_sprite); }

protected:
	Vector2f m_start_pos;
};