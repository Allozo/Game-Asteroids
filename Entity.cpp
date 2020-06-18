#include "Entity.h"

Entity::Entity() : life(true) {}

Entity::Entity(Animation &a, int _x, int _y, constants::nameClass _name, float _angle, float _radius) :
        anim(a),
        x(static_cast<float> (_x)),
        y(static_cast<float> (_y)),
        angle(_angle),
        R(_radius),
        life(true),
        name{_name} {}

void Entity::draw(sf::RenderWindow &app) {
    anim.get_sprite().setPosition(x, y);
    anim.get_sprite().setRotation(angle + 90);
    app.draw(anim.get_sprite());
}

constants::nameClass &Entity::get_name() {
    return name;
}