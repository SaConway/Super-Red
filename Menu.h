#pragma once
#include <vector>
#include <memory>
#include "Button.h"

//-----------------------------------------------------------------------------

class Menu
{
public:
	Menu(RenderWindow & window) :m_window(window) {};
	void mouseOnButton(Vector2f &);

protected:
	vector < shared_ptr< Button >> m_buttons;
	RenderWindow & m_window;
};

//-----------------------------------------------------------------------------

// Global functions
Vector2f getScaledBackgoundSize(const Texture &);