#include "Character.h"

void Character::init(Vector2f position, Vector2f size, int coll) {
	body.init(position, size, 1, 0.18, coll);
	body.set_velocity({ 0.f,0.f });
	body.set_acceleration({ 0.f,0.f });
	shape.setFillColor(Color::White);
	shape.setPosition(position);
	shape.setSize(size);
}

void Character::move(TileMap* tile_map, std::vector<RigidBody*> enem_bodies){
	body.move(tile_map, enem_bodies);
	shape.setPosition(body.position);
}
