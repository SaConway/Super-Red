#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>
#include <iostream>
#include <string>
#include <memory>
#include "MapLoader.h"
#include "Red.h"
#include "StageMenu.h"
#include "Button.h"
#include "EndLevelScreen.h"
#include "CollisionHandler.h"

//-----------------------------------------------------------------------------

/* Data stracture of all objects in this game, box2d world and map size */

struct MapData
{
	vector < vector< shared_ptr< GameObject >>> _game_object;
	vector < shared_ptr< AnimatedObject >> _animated_object;
	vector < shared_ptr< MovingObject >> _moving_object;
	vector < shared_ptr< GroundChainShape >> _ground_object;
	shared_ptr <Red> _red;
	unique_ptr <b2World> _box2dWorld;
	Vector2i _map_size;
};

//-----------------------------------------------------------------------------

/* Index of _game_object vector, i.e. witch object is at each row */

enum Index { I_Ground, I_Spike, I_Water, I_Environment, I_Coin, I_Chest, I_Mace, I_Saw };

/* Status of the game */

enum GameStatus {_Playing, _levelSuccess, _GameOver, _Pause, _GoToMenu};

/* Index of buttons */

enum ButtonIndex {_I_Pause, _I_Ok};


//-----------------------------------------------------------------------------

class Stage
{
	friend class EndLevelScreen;
public:
	Stage(string, RenderWindow &);
	GameStatus play();
	void clear();
	void menuHandler();
	void updateScore() { m_textScore.setString("Coins:\n" + to_string(++m_score)); }
	void updateGameStatus(GameStatus status) { m_game_status = status; }
	float SuccessPercent() { return (float)m_score / (float)m_data._game_object[I_Coin].size(); }
	void playWinSound() { m_winSound.play(); }
	void playLoseSound() { m_loseSound.play(); }
	void draw() const;

private:
	//private functions
	void input();
	void update();
	void move();
	void animation();
	void updateView();

	// Data
	MapData m_data;

	// SFML stuff
	RenderWindow & m_window;
	Sprite m_background;
	View m_view;
	Text m_textScore;
	Sound m_birdsSound ,m_loseSound, m_winSound;
	Time m_time ;
	Clock m_clock;

	// Utilities
	vector < shared_ptr< Button >> m_buttons;
	StageMenu m_stage_menu;
	CollisionHandler m_collision_handler;
	GameStatus m_game_status = GameStatus::_Playing;
	int m_score = 0;
};