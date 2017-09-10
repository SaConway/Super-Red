#include "EndLevelScreen.h"
#include "Stage.h"
#include <string>
//-----------------------------------------------------------------------------

/* ctor of EndLevelScreen class*/

EndLevelScreen::EndLevelScreen()
:m_button(Vector2f{ 0, 0 }, Vector2i{ 126, 125 }, Vector2i{ 128, 0 }, [this] {})
{
	// rectangle shade definition

	m_firstRectShade.setSize({ WINDOW_W, WINDOW_H });
	m_firstRectShade.setOrigin({ WINDOW_W / 2, WINDOW_H / 2 });
	m_firstRectShade.setScale({ 1.5f, 1.5f });
	m_firstRectShade.setFillColor(Color(40, 40, 40, 170));

	m_secondRectShade.setSize({ WINDOW_W / 3, WINDOW_H });
	m_secondRectShade.setOrigin({ WINDOW_W / 3 / 2, WINDOW_H / 2 });
	m_secondRectShade.setScale({ 1.5f, 1.5f });
	m_secondRectShade.setFillColor(Color(38, 38, 38, 170));

	// text definition

	m_textAtEnd.setFont(Resource::getInstance().getFont(FontID::_F_Font));
	m_textAtEnd.setCharacterSize(70);
	m_textLevelCompleted.setFont(Resource::getInstance().getFont(FontID::_F_Font));
	m_textLevelCompleted.setCharacterSize(100);
	m_textLevelCompleted.setString("LEVEL COMPLETED");
}

//-----------------------------------------------------------------------------

/* This function handle the process of the end level */

void EndLevelScreen::handleEndlevel(Stage & stage)
{
	Event event;
	//set text / rectangles shaders position and data. 
	utilEndLevel(stage.m_view,stage.m_score);

	while (true)
	{
		stage.draw();
		EndLevelScreen::draw(stage.m_window, stage.m_game_status);
		while (stage.m_window.pollEvent(event))
		{
			m_button.Hilight(stage.m_window.mapPixelToCoords(Mouse::getPosition()));

			switch (event.type)
			{
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Escape || event.key.code == Keyboard::Return) return;
				break;

			case Event::MouseButtonPressed:
				if (m_button.checkIfPressed(stage.m_window.mapPixelToCoords(Mouse::getPosition())))
				{
					m_button.handlePress();
					return;
				}
				break;
			}
		}
	}
}

//-----------------------------------------------------------------------------

/* This is an utulity function for handleEndlevel function */

void EndLevelScreen::utilEndLevel(View & view , int score)
{
	m_textAtEnd.setString("LEVEL SCORE\n" + std::to_string(score));

	m_textAtEnd.setPosition(view.getCenter().x - m_textAtEnd.getGlobalBounds().width / 2 - 20.f, view.getCenter().y + 250.f);
	m_textLevelCompleted.setPosition(view.getCenter().x - m_textLevelCompleted.getGlobalBounds().width / 2, view.getCenter().y - 600.f);
	m_firstRectShade.setPosition(view.getCenter());
	m_secondRectShade.setPosition(view.getCenter());
	m_button.setPosition(Vector2f{ m_textAtEnd.getPosition().x + m_textAtEnd.getGlobalBounds().width / 2.f - 64.f, m_textAtEnd.getPosition().y + m_textAtEnd.getGlobalBounds().height + 100.f });
}

//-----------------------------------------------------------------------------
 
/*print end level screen objects .*/

void EndLevelScreen::draw(RenderWindow & window, GameStatus game_status)
{
	window.draw(m_firstRectShade);
	window.draw(m_secondRectShade);
	window.draw(m_textAtEnd);
	if (game_status == GameStatus::_levelSuccess) window.draw(m_textLevelCompleted);
	m_button.draw(window);
	window.display();
}