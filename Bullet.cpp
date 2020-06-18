#include "Bullet.h"

Bullet::Bullet() = default;

Bullet::Bullet(Animation &a, int _x, int _y, constants::nameClass _name, float Angle, float radius)
        : Entity(a, _x, _y, _name, Angle, radius) {}

void Bullet::update() {
    dx = std::cos(angle * DegToRad) * 6;
    dy = std::sin(angle * DegToRad) * 6;
    x += dx;
    y += dy;

    if (x > constants::width_app || x < 0 || y > constants::height_app || y < 0) {
        life = false;
    }
}
