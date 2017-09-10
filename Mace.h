#pragma once
#include <SFML/Graphics.hpp>
#include "Box2D\Box2D.h"
#include "MovingObject.h"

//-----------------------------------------------------------------------------

const Int32 MACE_SPEED = 10;

//-----------------------------------------------------------------------------

class Mace : public MovingObject
{
public:
	Mace(Vector2f &, Vector2i &, Vector2i &, unique_ptr <b2World> &);
	void animate() override {};
	void move() override;
	void handleColision() { m_direction *= -1.f; }
	void setStartPos() override;

private:
	float32 m_direction;
};