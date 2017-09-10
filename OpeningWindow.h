#pragma once
#include <SFML/Graphics.hpp>

//-----------------------------------------------------------------------------

using namespace std;
using namespace sf;

//-----------------------------------------------------------------------------

class OpeningWindow
{
public:
	OpeningWindow(RenderWindow &);
	void drawSR() const;
	void drawPG() const;

private:
	Text m_textSR, m_textPG;
	RenderWindow & m_window;
};