#pragma once
#include "Box2D\Box2D.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "BodyObject.h"
#include "MovingObject.h"

//-----------------------------------------------------------------------------

/* Directions that red can move */

enum Command { _Right, _UpRight, _UpLeft, _Left, _Up, _Down, _Still };
enum Direction { _R, _L};

const int NUM_OF_RED_PIC = 14;
const Time STEP_SOUND_SPEED = seconds(0.3f);

//-----------------------------------------------------------------------------

class Red : public MovingObject
{
public:
	Red(Vector2f &, Vector2i &, Vector2i &, unique_ptr <b2World> &);
	b2Body * getBody() { return m_body; }
	void landingOnGround(int);
	int getNumOfFootContact() const { return m_numFootContacts; }
	Vector2f getPosition() const { return m_sprite.getPosition(); }
	void setPosition() { m_sprite.setPosition({ (float)m_body->GetPosition().x * RATIO , (float)m_body->GetPosition().y * RATIO });};
	void setDirection(Command direction) { m_command = direction; }
	void animate() override;
	void move() override;
	void setStartPos() override;

private:
	void stepSoundManager();
	void animationControl(int x, int y) { m_pos_in_pic = { x,y }; }

	Command m_command = Command::_Down;
	Direction m_direction = Direction::_R;

	int m_soundCounter = 0;
	int m_numFootContacts = 0;
	int m_current_pic;
	
	// red in air movment animation varibles
	bool m_down_press;

	//step sound variables
	Sound m_stepSound[6];
	Sound m_jumpSound;
	Clock m_step_clock;
};