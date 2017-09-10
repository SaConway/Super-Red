#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"

//-----------------------------------------------------------------------------

const float OFFSET = -1.f;

//-----------------------------------------------------------------------------

//info screen class defenition

class InfoManager : public Menu
{
public:
	InfoManager(RenderWindow &);
	void runInfo();

private:
	//functions
	void displayInfo();
	bool eventHandler();
	void updateObjectState();

	//variables
	Sprite m_background;
	String m_string;
	Text m_text;
	Vector2f m_text_start_pos;
	Clock m_clock;
	Time m_time;
};