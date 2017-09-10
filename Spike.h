#pragma once
#include <SFML/Graphics.hpp>
#include "InanimateObject.h"
#include "BodyObject.h"

//-----------------------------------------------------------------------------

class Spike : public InanimateObject , public BodyObject
{
public:
	Spike(Vector2f &, Vector2i &, Vector2i &, unique_ptr <b2World> &);
};