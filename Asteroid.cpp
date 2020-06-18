#include "Asteroid.h"

Asteroid::Asteroid() = default;

void Asteroid::update() {
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

Asteroid::Asteroid(Animation &a, int _x, int _y, constants::nameClass _name, float _angle, float _radius)
        : Entity(a, _x, _y, _name, _angle, _radius) {
    std::uniform_real_distribution<float> di(-4, 3);
    dx = di(constants::dre);
    dy = di(constants::dre);
}

