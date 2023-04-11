#include "Character.h"

void Character::init(Vector2f _position, Vector2f _size, Texture _texture, short int _collision) {
	position = _position;
	size = _size;
	collision = _collision;
	texture = _texture;
	//sprite.setTexture(texture);
	sprite.setSize(_size);
	sprite.setFillColor(Color::White);

	//debug
	if (font.loadFromFile("Fonts/Disket-Mono-Regular.ttf"))
	text.setFillColor(Color::White);
	text.setFont(font);
	text.setPosition({ 100,100 });
	text.setCharacterSize(12);
	text.setStyle(sf::Text::Regular | sf::Text::Underlined);
}

void Character::set_velocity(Vector2f _velocity) {
	velocity = _velocity;
}

void Character::move(TileMap tile_map) {
	Vector2f old_velocity = velocity;
	velocity = tile_map.collide(position, size, velocity, collision);
	position += velocity;
	sprite.setPosition(position);
	//debug
	debug = "position: x " + std::to_string(position.x) + " y " + std::to_string(position.y)
		+ "\nvelocity: x " + std::to_string(velocity.x) + " y " + std::to_string(velocity.y)
		+ "\nold_velo: x " + std::to_string(old_velocity.x) + " y " + std::to_string(old_velocity.y);
	text.setString(debug);
//	text.setPosition((Vector2f)position);
}