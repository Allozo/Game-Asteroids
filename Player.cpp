#include "Player.h"

Player::Player() = default;

Player::Player(Animation &a, int _x, int _y, constants::nameClass _name, float _angle, float radius)
        : Entity(a, _x, _y, _name, _angle, radius) {}

void Player::update() {
    if (thrust) {
        dx += static_cast<float> (std::cos(angle * DegToRad) * 0.2);
        dy += static_cast<float> (std::sin(angle * DegToRad) * 0.2);
    } else {
        dx *= deceleration_rate;
        dy *= deceleration_rate;
    }


    float speed = std::sqrt(dx * dx + dy * dy);
    if (speed > maxSpeed) {
        dx *= maxSpeed / speed;
        dy *= maxSpeed / speed;
    }

    x += dx;
    y += dy;

    if (x > constants::width_app) {
        x = 0;
    }
    if (x < 0) {
        x = constants::width_app;
    }
    if (y > constants::height_app) {
        y = 0;
    }
    if (y < 0) {
        y = constants::height_app;
    }
}

