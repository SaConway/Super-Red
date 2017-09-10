#include "Button.h"
#include "Resource.h"

//-----------------------------------------------------------------------------

/* C-tor's of Button*/

Button::Button(Vector2f & pos_by_pixel, Vector2i & size_of_pic, Vector2i & pos_in_pic, function<void()> func)
{
	m_button.setTexture(Resource::getInstance().getTexture(TextureID::_T_Buttons));
	m_clickSound.setBuffer(Resource::getInstance().getSound(SoundID::_S_Click));
	initButton(pos_by_pixel,size_of_pic, pos_in_pic , func);
}

//-------------------

Button::Button(const Texture & text , Vector2f & pos_by_pixel, Vector2i & size_of_pic, Vector2i & pos_in_pic, function<void()> func)
{
	m_button.setTexture(text);
	initButton(pos_by_pixel, size_of_pic, pos_in_pic, func);
}

//-------------------

Button::Button(const SoundBuffer & sound, Vector2f & pos_by_pixel, Vector2i & size_of_pic, Vector2i & pos_in_pic, function<void()> func )
{
	m_button.setTexture(Resource::getInstance().getTexture(TextureID::_T_Buttons));
	m_clickSound.setBuffer(sound);
	initButton(pos_by_pixel, size_of_pic, pos_in_pic, func);
}

//-------------------

void Button::initButton(Vector2f & pos_by_pixel, Vector2i & size_of_pic, Vector2i & pos_in_pic , function<void()> func)
{
	m_button.setTextureRect({ pos_in_pic,size_of_pic });
	m_button.setPosition(pos_by_pixel);
	m_func = func;
}

//-----------------------------------------------------------------------------

/* This function set hilight of button according to mouse position */

void Button::Hilight(Vector2f & mouse_pos)
{
	if (checkIfPressed(mouse_pos)) m_button.setColor(Color(220, 220, 220, 240));
	else m_button.setColor(Color(255, 255, 255, 255));
}

//-----------------------------------------------------------------------------

/* This function handle the process of button pressed */

void Button::handlePress()
{
	playClickSound();

	if (m_func) m_func();
}
