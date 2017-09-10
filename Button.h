#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <functional>

//-----------------------------------------------------------------------------

using namespace sf;
using namespace std;

//-----------------------------------------------------------------------------

const int BUTTONS_SIZE = 128;

//-----------------------------------------------------------------------------

class Button 
{
public:
	Button(Vector2f&, Vector2i &, Vector2i&, function<void()>);
	Button(const Texture & ,Vector2f&, Vector2i&, Vector2i&, function<void()>);
	Button(const SoundBuffer & , Vector2f&, Vector2i&, Vector2i&, function<void()>);

	bool checkIfPressed(Vector2f & mouse_loc) const { return m_button.getGlobalBounds().contains(mouse_loc); };
	void setPosition(Vector2f & pos) { m_button.setPosition(pos); }
	void setScale(Vector2f scale) { m_button.setScale(scale); };
	void setOrigin(Vector2f origin) { m_button.setOrigin(origin); };
	const Vector2f & getPosition() const { return m_button.getPosition(); }
	void Hilight(Vector2f &);
	void handlePress();
	void playClickSound() { m_clickSound.play(); }
	void draw(RenderWindow & window) const { window.draw(m_button); }

private:
	void initButton(Vector2f & , Vector2i & , Vector2i & , function<void()>);
	Sound m_clickSound;
	Sprite m_button;
	function<void()> m_func;
};