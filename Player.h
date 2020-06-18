#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity {
    const float maxSpeed = 15;
    const float deceleration_rate = 0.99;
public:
    Player();

    Player(Animation &a, int _x, int _y, constants::nameClass _name, float _angle = 0, float radius = 1);

    bool thrust{};

    void update() override;
};

#endif