#ifndef ENTITY_H
#define ENTITY_H

#include "Animation.h"
#include "constant.h"
#include <SFML/Graphics.hpp>

class Entity {
    constants::nameClass name;
public:
    bool life;
    float x, y, dx, dy, R, angle;
    Animation anim;
    const float DegToRad = 0.017453f;

    Entity();

    Entity(Animation &a, int _x, int _y, constants::nameClass _name, float _angle = 0, float _radius = 1);

    void draw(sf::RenderWindow &app);

    constants::nameClass &get_name();

    virtual void update() {};

    virtual ~Entity() = default;
};

#endif