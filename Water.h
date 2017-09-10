#pragma once
#include "NotMovingObject.h"
#include <SFML/Graphics.hpp>
#include "Box2D\Box2D.h"
#include <memory>

//-----------------------------------------------------------------------------

const Int32 SPEED_WATER = 100;
const int NUM_OF_WATER_PIC = 16;

//-----------------------------------------------------------------------------

class Water : public NotMovingObject
{
public:
	Water(Vector2f &, Vector2i &, Vector2i &, unique_ptr <b2World> &);
	void draw(RenderWindow & window) const override{ window.draw(m_sprite); }
	void animate() override;
};