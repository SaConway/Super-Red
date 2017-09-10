#include "Saw.h"

//-----------------------------------------------------------------------------

/* C-tor of Saw */

Saw::Saw(Vector2f & pos_by_pixel, Vector2i & size_of_pic, Vector2i & pos_in_pic, unique_ptr <b2World> & world)
	:MovingObject(Resource::getInstance().getTexture(TextureID::_T_Saw), pos_by_pixel, size_of_pic, pos_in_pic)
{
	//randomize saw direction
	m_direction = (rand() % 2 == 0) ? -1.f : 1.f;

	m_sprite.setOrigin(size_of_pic.x / 2.f, size_of_pic.y / 2.f);  //for rotation 
	m_speed = milliseconds(SPEED_SAW);

	b2BodyDef body_def;
	b2FixtureDef fixture_def;
	b2CircleShape def_shape;
	
	//Set collition group
	fixture_def.filter.categoryBits = Collition_Group::ENEMY;
	fixture_def.filter.maskBits = Collition_Group::GROUND | Collition_Group::RED;
	
	//Create our box2D body
	def_shape.m_radius = (size_of_pic.x-40.f)/2.f/RATIO;
	body_def.position.Set((float32)pos_by_pixel.x / RATIO , (float32)pos_by_pixel.y / RATIO);
	body_def.type = b2_dynamicBody;

	fixture_def.shape = &def_shape;
	fixture_def.density = 1.f;
	fixture_def.friction = 0.0f;

	m_body = world->CreateBody(&body_def);
	m_body->CreateFixture(&fixture_def);

	m_body->SetUserData(this);
	m_body->SetGravityScale(1);
}

//-----------------------------------------------------------------------------

/* This function animate the Saw */

void Saw::animate()
{
	m_angle++;
	m_angle %= 360;
	m_sprite.setRotation((float)m_angle);
}

//-----------------------------------------------------------------------------

/* This function move the Saw */

void Saw::move()
{
	if (m_clock.getElapsedTime() > m_speed)
	{
		m_clock.restart();
		m_body->SetLinearVelocity(b2Vec2(3.5f * m_direction, 0));
		m_sprite.setPosition({ m_body->GetPosition().x * RATIO, m_body->GetPosition().y * RATIO });
	}
}

//-----------------------------------------------------------------------------

/* This function set position of Saw to the start postion */

void Saw::setStartPos()
{
	m_sprite.setPosition(m_start_pos);
	m_body->SetTransform({(float32)m_start_pos.x / RATIO, (float32)m_start_pos.y / RATIO }, 0);
}