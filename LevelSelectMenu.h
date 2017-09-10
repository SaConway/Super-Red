#pragma once
#include <array>
#include <memory>
#include <vector>
#include "Menu.h"
#include "Button.h"
#include "Cloud.h"
#include "LevelIcon.h"

//-----------------------------------------------------------------------------

const int NUM_OF_LEVELS = 5;
enum op_level_select_menu{_BackToMainMenu, Level1, _Level2, _Level3, _Level4, _Level5, _Stay};
const int NUM_OF_CLOUDS_LEVEL = 10;
//-----------------------------------------------------------------------------

class LevelSelectMenu : public Menu
{
public:
	LevelSelectMenu(RenderWindow &);
	op_level_select_menu run();
	void handleLevelSuccess(int, float);

private:
	//functions
	op_level_select_menu eventHandler();
	void updateClouds() { for (auto &i : m_clouds) i->move(); }
	void updateLevelSuccess(int level) { m_level_icons[level].setSuccess(true); }
	void updateLevelAccess(int level) { if(level < NUM_OF_LEVELS) m_level_icons[level].setAccess(true); }
	void updateStars(int level, int stars) { m_level_icons[level].updateStars(stars); }
	void draw() const;

	//variables
	vector <LevelIcon> m_level_icons;
	array<unique_ptr<Cloud>, NUM_OF_CLOUDS_LEVEL> m_clouds;
	Sprite m_background;
};