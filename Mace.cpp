#include "Mace.h"

//-----------------------------------------------------------------------------

/* C-tor of Mace */

Mace::Mace(Vector2f & pos_by_pixel, Vector2i & size_of_pic, Vector2i & pos_in_pic, unique_ptr <b2World> & world)
	:MovingObject(Resource::getInstance().getTexture(TextureID::_T_Mace), pos_by_pixel, size_of_pic, pos_in_pic)
{
	//randomize mace direction
	m_direction = (rand() % 2 == 0) ? -1.f : 1.f;

	m_sprite.setOrigin(float(size_of_pic.x / 2), float(size_of_pic.y / 2));
	m_speed = milliseconds(MACE_SPEED);

	b2BodyDef body_def;
	b2FixtureDef fixture_def;
	b2PolygonShape def_shape;

	//set collition group
 	fixture_def.filter.categoryBits = Collition_Group::ENEMY  ;
	fixture_def.filter.maskBits = Collition_Group::GROUND | Collition_Group::RED;
	
	//Create our box2D body
	body_def.position.Set((float32)pos_by_pixel.x / RATIO, (float32)pos_by_pixel.y / RATIO);
	body_def.type = b2_dynamicBody;
	def_shape.SetAsBox((float32)((size_of_pic.x-64.f) / 2.f) / RATIO, (float32)((size_of_pic.y-64.f) / 2.f) / RATIO);

	body_def.fixedRotation = true;
	fixture_def.shape = &def_shape;
	fixture_def.density = 1.0f;
	fixture_def.friction = 0.f;

	m_body = world->CreateBody(&body_def);
	m_body->CreateFixture(&fixture_def);

	m_body->SetUserData(this);
	m_body->SetGravityScale(0);
}

//-----------------------------------------------------------------------------

/* This function move the Mace */

void Mace::move()
{
	if (m_clock.getElapsedTime() > m_speed)
	{
		m_clock.restart();
		m_body->SetLinearVelocity(b2Vec2(0, 3.5f *  m_direction));
		m_sprite.setPosition({m_body->GetPosition().x * RATIO, m_body->GetPosition().y * RATIO });
	}
}

//-----------------------------------------------------------------------------

/* This function set position of mace to the start postion */

void Mace::setStartPos()
{
	m_sprite.setPosition(m_start_pos);
	m_body->SetTransform({(float32)m_start_pos.x / RATIO, (float32)m_start_pos.y / RATIO }, 0);
}