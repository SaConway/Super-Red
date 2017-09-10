#include "OpeningWindow.h"
#include "Resource.h"
//-----------------------------------------------------------------------------

/* C-tor of OpeningWindow */

OpeningWindow::OpeningWindow(RenderWindow & window)
	: m_window(window)
{
	m_window.clear({ 0, 0, 0, 0 });

	// text definition

	m_textSR.setCharacterSize(80);
	m_textSR.setFont(Resource::getInstance().getFont(FontID::_F_Font));
	m_textSR.setFillColor(Color(255, 0, 0, 255));
	m_textSR.setString("SUPER RED");
	m_textSR.setPosition(Vector2f{ float(WINDOW_H) / 2, float(VideoMode::getDesktopMode().height) / 2 - m_textSR.getLocalBounds().height / 2 });
	
	m_textPG.setCharacterSize(30);
	m_textPG.setFont(Resource::getInstance().getFont(FontID::_F_Font));
	m_textPG.setFillColor(Color(255, 255, 255, 255));
	m_textPG.setString("a platform game");
	m_textPG.setPosition(Vector2f{ m_textSR.getPosition().x + m_textSR.getLocalBounds().width / 6.f,  m_textSR.getPosition().y + m_textSR.getLocalBounds().height + 10.f });
}

//-----------------------------------------------------------------------------

/* This function draw OpeningWindow stuf before loading */

void OpeningWindow::drawSR() const
{
	m_window.draw(m_textSR);
	m_window.display();
}

//-----------------------------------------------------------------------------

/* This function draw OpeningWindow stuf after loading */

void OpeningWindow::drawPG() const
{
	Clock clock;
	clock.restart();

	m_window.draw(m_textSR);
	m_window.draw(m_textPG);
	m_window.display();

	while (clock.getElapsedTime() < seconds(3)){}
}