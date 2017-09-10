#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

//-----------------------------------------------------------------------------

enum GameStatus;
class Stage;
//-----------------------------------------------------------------------------

using namespace sf;
using namespace std;

//-----------------------------------------------------------------------------

class EndLevelScreen
{
public:
	EndLevelScreen();
	void handleEndlevel(Stage &);

private:
	void utilEndLevel(View & , int );
	void draw(RenderWindow & window, GameStatus game_status) ;
	Text m_textAtEnd, m_textLevelCompleted;
	RectangleShape m_firstRectShade, m_secondRectShade; // for end level effect
	Button m_button;
};

