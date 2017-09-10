#pragma once
#include "AnimatedObject.h"
#include "BodyObject.h"
#include <SFML/Graphics.hpp>

//-----------------------------------------------------------------------------

class NotMovingObject : public AnimatedObject , public BodyObject
{
public:
	NotMovingObject(const Texture &, Vector2f &, Vector2i &, Vector2i &, unique_ptr <b2World> &);
	virtual ~NotMovingObject() {};
};