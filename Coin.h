#pragma once
#include "NotMovingObject.h"
#include <SFML/Graphics.hpp>
#include "Box2D\Box2D.h"
#include <memory>

//-----------------------------------------------------------------------------

const Int32 SPEED_COIN = 50;
const int NUM_OF_COIN_PIC = 16;

//-----------------------------------------------------------------------------

class Coin : public NotMovingObject
{
public:
	Coin(Vector2f &, Vector2i &, Vector2i &, unique_ptr <b2World> &);
	void draw(RenderWindow & window) const { if (m_on_map) window.draw(m_sprite); }
	void setOnMap(bool onMap) { m_on_map = onMap; }
	bool isOnMap() const { return m_on_map; }
	void animate() override;
	void playSound() { m_coin_sound.play(); }

private:
	bool m_on_map = true;
	static Sound m_coin_sound;
};