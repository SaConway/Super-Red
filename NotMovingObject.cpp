#include "NotMovingObject.h"

//-----------------------------------------------------------------------------

/* C-tor of NotMovingObject */

NotMovingObject::NotMovingObject(const Texture & text, Vector2f & pos_by_pixel, Vector2i & size_of_pic, Vector2i & pos_in_pic, unique_ptr <b2World> & world)
	:AnimatedObject(text, pos_by_pixel, size_of_pic, pos_in_pic)
{
	b2BodyDef body_def;
	b2FixtureDef fixture_def;
	b2PolygonShape def_shape;

	//Create our box2D body
	body_def.type = b2_staticBody;
	body_def.position.Set((float32)pos_by_pixel.x / RATIO, (float32)pos_by_pixel.y / RATIO);
	def_shape.SetAsBox((float32)(size_of_pic.x / 2.f) / RATIO, (float32)(size_of_pic.y / 2.f) / RATIO);

	m_body = world->CreateBody(&body_def);

	fixture_def.shape = &def_shape;
	fixture_def.density = 1.0f;
	fixture_def.friction = 1.f;

	m_body->CreateFixture(&fixture_def);
}
