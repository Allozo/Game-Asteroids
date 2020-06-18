#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet : public Entity {
public:
    Bullet();

    Bullet(Animation &a, int _x, int _y, constants::nameClass _name, float Angle = 0, float radius = 1);

    void update() override;
};

#endif