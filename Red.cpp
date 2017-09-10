#include "Red.h"
//-----------------------------------------------------------------------------

/* C-tor of red */

Red::Red(Vector2f & pos_by_pixel, Vector2i & size_of_pic, Vector2i & pos_in_pic, unique_ptr <b2World> & world)
	:MovingObject(Resource::getInstance().getTexture(TextureID::_T_Red), pos_by_pixel, size_of_pic, pos_in_pic), m_current_pic(0)
{
	m_step_clock.restart();
	// sprite offset
	m_sprite.setOrigin(32, 150);

	// sound definition
	m_jumpSound.setBuffer(Resource::getInstance().getSound(SoundID::_S_Jump));
	m_stepSound[0].setBuffer(Resource::getInstance().getSound(SoundID::_S_Player_Step1));
	m_stepSound[1].setBuffer(Resource::getInstance().getSound(SoundID::_S_Player_Step2));
	m_stepSound[2].setBuffer(Resource::getInstance().getSound(SoundID::_S_Player_Step3));
	m_stepSound[3].setBuffer(Resource::getInstance().getSound(SoundID::_S_Player_Step4));
	m_stepSound[4].setBuffer(Resource::getInstance().getSound(SoundID::_S_Player_Step5));
	m_stepSound[5].setBuffer(Resource::getInstance().getSound(SoundID::_S_Player_Step6));

	//render position with box2d world
	sf::Vector2f renderPos = pos_by_pixel + sf::Vector2f(0.f, size_of_pic.y / 2.f);
	sf::Vector2f centerPlayerPos = sf::Vector2f(renderPos.x,renderPos.y);

	//Create our box2D body

	b2BodyDef body_def;
	body_def.fixedRotation = true;
	body_def.type = b2_dynamicBody;
	body_def.position.Set(centerPlayerPos.x / RATIO, (centerPlayerPos.y) / RATIO);
	m_body = world->CreateBody(&body_def);

	//set main body polygon of red
	b2Vec2 body_vec[7];
	b2PolygonShape body_shape;
	body_vec[0].Set(0, 0);
	body_vec[1].Set(-39.f / RATIO, -18.f / RATIO);
	body_vec[2].Set(-10.f / RATIO, -130.f / RATIO);
	body_vec[3].Set(87.f / RATIO, -130.f / RATIO);
	body_vec[4].Set(123.f / RATIO, -94.f / RATIO);
	body_vec[5].Set(117.f / RATIO, -1.f / RATIO);
	body_vec[6].Set(5.f / RATIO, 0);

	b2FixtureDef body_fixture;
	body_shape.Set(body_vec, 7);
	body_fixture.shape = &body_shape;
	body_fixture.density = 1.f;
	body_fixture.friction = 1.0f; //how slippery it is
	body_fixture.restitution = 0.0f;

	
	//set collition group
	body_fixture.filter.categoryBits = Collition_Group::RED; // i'am red
	m_body->CreateFixture(&body_fixture);

	//create foot body sensor for collition detection 
	b2Vec2 legs[5];
	legs[0].Set(0, 0);
	legs[1].Set(0, 21.f / RATIO);
	legs[2].Set(87.f / RATIO, 21.f / RATIO);
	legs[3].Set(88.f / RATIO, -2.f / RATIO);
	legs[4].Set(2.f / RATIO, 0);

	b2PolygonShape legs_shape;
	legs_shape.Set(legs, 5);
	b2FixtureDef footFixture;
	footFixture.isSensor = true;
	footFixture.filter.categoryBits = Collition_Group::RED; // i'am red (for collision)
	footFixture.shape = &legs_shape;
	footFixture.density = 1.f;
	m_body->CreateFixture(&footFixture);
	b2Fixture * footSensorFixture = m_body->CreateFixture(&footFixture);
	footSensorFixture->SetUserData(this);
	m_body->SetUserData(this);
}

//-----------------------------------------------------------------------------

/* This function move Red */

void Red::move()
{

	b2Vec2 move_vel = m_body->GetLinearVelocity();

	if (move_vel == b2Vec2{ 0,0 })
		m_down_press = true;			//this variable allow player to press down only once while in the air.

	switch (m_command)
	{
		case _Right:
		{
			m_direction = Direction::_R;
			// red is on ground
			if (m_numFootContacts > 0) 
				stepSoundManager();
			else
				m_command = Command::_UpRight;		// switch to up right for animation.

			move_vel.x = 5;
			m_body->SetLinearVelocity(move_vel);
			break;
		}

		case _Left:
		{
			m_direction = Direction::_L;
			// red is on ground
			if (m_numFootContacts > 0)
				stepSoundManager();
			else
				m_command = Command::_UpLeft;		// switch to up left for animation.

			move_vel.x = -5;
			m_body->SetLinearVelocity(move_vel);
			break;
		}

		case _UpRight:
		{
			// red is on ground
			if (m_numFootContacts > 0)
			{
				m_jumpSound.play();
				move_vel = b2Vec2(5, -20);
				m_body->SetLinearVelocity(move_vel);
			}
			else
			{
				move_vel.x = 5;
				m_body->SetLinearVelocity(move_vel);
			}
			m_direction = Direction::_R;
			break;
		}

		case _UpLeft:
		{
			// red is on ground
			if (m_numFootContacts > 0)
			{
				m_jumpSound.play();
				move_vel = b2Vec2(-5, -20);
				m_body->SetLinearVelocity(move_vel);
			}
			else {
				move_vel.x = -5;
				m_body->SetLinearVelocity(move_vel);
			}
			m_direction = Direction::_L;
 			break;
		}

		case _Up:
		{
 			// red is on ground
       		if (m_numFootContacts > 0)
			{
				m_jumpSound.play();
				move_vel.y = -20;
				m_body->SetLinearVelocity(move_vel);
			}
			break;
		}

		case _Down:
			if (m_down_press) {
				move_vel.y = move_vel.y * 0.5f;
				m_body->SetLinearVelocity(move_vel);
				m_down_press = false;
			}
			break;

		case _Still:
			setPosition();
	}
}

//-----------------------------------------------------------------------------

/* This function animate red */

void Red::animate()
{
	switch (m_command)
	{
	case _Right:
		//change to walking right animation
		if (m_numFootContacts > 0) {
			m_current_pic = (m_current_pic + 3) % NUM_OF_RED_PIC;
			animationControl(m_current_pic * m_sprite.getTextureRect().width, 0);
		}
		break;

	case _Left:
		//change to walking left animation
		if (m_numFootContacts > 0) {
			m_current_pic = (m_current_pic + 3) % NUM_OF_RED_PIC;
			animationControl(m_current_pic * m_sprite.getTextureRect().width, m_sprite.getTextureRect().height);
		}
		break;

	case _UpRight:
		//change picture to right animation
		animationControl(0, 2 * (m_sprite.getTextureRect().height + 1));
		break;

	case _UpLeft:
		//change picture to left animation
		animationControl(m_sprite.getTextureRect().width, 2 *(m_sprite.getTextureRect().height + 1));
		break;

	case _Up:
		if (m_direction == Direction::_R) animationControl(0, 2 * (m_sprite.getTextureRect().height  + 1));
		else if (m_direction == Direction::_L) animationControl(m_sprite.getTextureRect().width, 2 * (m_sprite.getTextureRect().height + 1));
		break;

	case _Still:
		//if red is on ground
		if (m_numFootContacts > 0 )
		{
			if (m_pos_in_pic.y == m_sprite.getTextureRect().height * 2)
				if (m_direction == Direction::_R)
					animationControl(0, 0);
				else
					animationControl( 0, m_sprite.getTextureRect().height);
		}
	}
	//set texture sprite according to animation changes above...
	m_sprite.setTextureRect({ m_pos_in_pic, Vector2i{m_sprite.getTextureRect().width,m_sprite.getTextureRect().height }});
}

//-----------------------------------------------------------------------------

/*This function update data when red is landing on ground*/
void Red::landingOnGround(int number)
{
	if (m_numFootContacts == 0) 
	{
		if (m_direction == Direction::_L)
			m_pos_in_pic = { 0, m_sprite.getTextureRect().height };
		else if (m_direction == Direction::_R)
			m_pos_in_pic = { 0,0 };
	}
	m_numFootContacts = number;
}

//-----------------------------------------------------------------------------

/* This function set position of red to the start postion */

void Red::setStartPos()
{
	m_sprite.setPosition(m_start_pos);
	m_body->SetTransform({ (float32)m_start_pos.x / RATIO, (float32)m_start_pos.y / RATIO }, 0);
	m_command = _Down;
	m_body->SetLinearVelocity(b2Vec2{ 0,10 });
	if (m_pos_in_pic.y == 0)
		m_direction = Direction::_R;
	else
		m_direction = Direction::_L;
}

//-----------------------------------------------------------------------------

/*This function manage the step sound according to the m_step_clock */

void Red::stepSoundManager()
{
	if (m_step_clock.getElapsedTime() > STEP_SOUND_SPEED)
	{
		m_step_clock.restart();
		m_stepSound[(++m_soundCounter % 6)].play();
	}
}