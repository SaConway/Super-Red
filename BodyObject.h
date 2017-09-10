#pragma once
#include <SFML/Graphics.hpp>
#include "Box2D\Box2D.h"

//-----------------------------------------------------------------------------

using namespace sf;
using namespace std;

//-----------------------------------------------------------------------------

/* Convert ration between box2d world to sfml world (pixel to metric) */
const float RATIO = 32.8f;

/* Collition groups*/
enum Collition_Group {GROUND = 0x0002, ENEMY = 0x0004, COIN = 0x0008, RED = 0x0010,};

//-----------------------------------------------------------------------------

class BodyObject
{
public:
	BodyObject() = default;

protected:
	b2Body * m_body;	//box2d World object
};