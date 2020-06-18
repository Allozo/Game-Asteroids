#ifndef ASTEROID_H
#define ASTEROID_H

#include "Entity.h"

class Asteroid : public Entity {
public:
    Asteroid();

    Asteroid(Animation &a, int _x, int _y, constants::nameClass _name, float _angle = 0, float _radius = 1);

    void update() override;
};

#endif