#pragma once
#include "MovingObject.h"
#include <SFML/Graphics.hpp>
#include "Box2D\Box2D.h"
#include <memory>

//-----------------------------------------------------------------------------

const Int32 SPEED_SAW = 10;

//-----------------------------------------------------------------------------

class Saw : public MovingObject
{
public:
	Saw(Vector2f &, Vector2i &, Vector2i &, unique_ptr <b2World> &);
	void animate() override;
	void move() override;
	void handleColision() { m_direction *= -1.f; }
	void setStartPos() override;

private:
	float32 m_direction;
	int m_angle = 0;
};