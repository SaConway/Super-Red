#include "Menu.h"

//-----------------------------------------------------------------------------

/* This function highlight the hovered button */

void Menu::mouseOnButton(Vector2f & mouse_pos)
{
	for (int i = 0; i < m_buttons.size(); i++) 
		m_buttons[i]->Hilight(mouse_pos);
}

//-----------------------------------------------------------------------------

/* This function return scale fix for background */

Vector2f getScaledBackgoundSize(const Texture & text)
{
	return Vector2f((float)VideoMode().getDesktopMode().width / (float)text.getSize().x,
	                (float)VideoMode().getDesktopMode().height / (float)text.getSize().y);
}
