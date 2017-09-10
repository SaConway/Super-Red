#include "GroundChainShape.h"

//-----------------------------------------------------------------------------

/* C-tor ground chain shape */

GroundChainShape::GroundChainShape(b2Vec2 * vec, unique_ptr <b2World> &world, size_t num_of_vertex)
{
	b2ChainShape shape;
	b2BodyDef body_def;
	b2FixtureDef fixture_def;

	body_def.type = b2_staticBody;
	m_body = world->CreateBody(&body_def);

	shape.CreateChain(vec, (int32)num_of_vertex);
	fixture_def.shape = &shape;
	m_body->CreateFixture(&fixture_def);

	//set collition group
	b2Filter filter;
	filter.categoryBits = Collition_Group::GROUND;
	m_body->GetFixtureList()->SetFilterData(filter);

	m_body->SetUserData(this);
}