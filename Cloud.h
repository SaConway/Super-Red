#pragma once
#include <SFML/Graphics.hpp>
#include "Box2D\Box2D.h"

//-----------------------------------------------------------------------------

using namespace std;
using namespace sf;

//-----------------------------------------------------------------------------

const int NUM_OF_CLOUD_PIC = 2;

//-----------------------------------------------------------------------------

class Cloud 
{
public:
	Cloud();
	void move();
	void draw(RenderWindow & window) { window.draw(m_sprite); };

private:
	Sprite m_sprite;
	Clock m_clock;
	Time m_speed;
};