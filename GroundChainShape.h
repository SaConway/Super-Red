#pragma once
#include <Box2D\Box2D.h>
#include <memory>
#include <vector>
#include "BodyObject.h"
#include "WorldObject.h"

//-----------------------------------------------------------------------------

using namespace std;

//-----------------------------------------------------------------------------

class GroundChainShape :public WorldObject, public BodyObject 
{
public:
	GroundChainShape(b2Vec2 * , unique_ptr <b2World> &, size_t);
};