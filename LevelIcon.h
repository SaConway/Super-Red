#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Button.h"

//-----------------------------------------------------------------------------

const int NUM_OF_STARS = 3;

//-----------------------------------------------------------------------------

class LevelIcon
{
public:
	LevelIcon(int, float);
	void draw(RenderWindow &) const;
	bool getIsAccess() const { return m_levelAccess; }
	bool getIsSuccess() const { return m_levelSuccess; }
	void setSuccess(bool status) { m_levelSuccess = status; }
	void setAccess(bool access) { m_levelAccess = access; }
	bool isLevelSelected(Vector2f & mouse_pos) { return m_door->checkIfPressed(mouse_pos); }
	void hilight(Vector2f & mouse_pos) { m_door->Hilight(mouse_pos); }
	void updateStars(int);
	void updateSign() { m_levelSign.first.setTextureRect({130, 0, 129, 53}); }
	void handlePress() { m_door->handlePress(); }

private:
	pair<Sprite, Text> m_levelSign;
	shared_ptr< Button > m_door;
	Sprite m_tape;
	array<Sprite, NUM_OF_STARS> m_stars;
	bool m_levelAccess = false;
	bool m_levelSuccess = false;
	int m_numOfStars = 0;
};