#pragma once
#include "NotMovingObject.h"
#include <SFML/Graphics.hpp>
#include "Box2D\Box2D.h"

//-----------------------------------------------------------------------------

const int SPEED_CHEST = 350;
const int NUM_OF_CHEST_PIC = 6;

//-----------------------------------------------------------------------------

class Chest : public NotMovingObject
{
public:
	Chest(Vector2f &, Vector2i &, Vector2i &, unique_ptr <b2World> &);
	virtual void draw(RenderWindow & window) const { window.draw(m_sprite); }
	void animate() override;
};