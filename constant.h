#ifndef CONSTANT_H
#define CONSTANT_H

#include <random>

namespace constants {
    static std::default_random_engine dre;

    enum nameClass {
        name_Asteroid = 10, name_Bullet, name_Player, name_Explosion
    };

    const int height_app = 800;
    const int width_app = 1200;
}

#endif