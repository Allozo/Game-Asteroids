#ifndef GAME_H
#define GAME_H

#include "Asteroid.h"
#include "Bullet.h"
#include "Entity.h"
#include <list>
#include <memory>
#include "Player.h"
#include <sstream>


class Game {
    const float speed_rotation_spaceship = 3;

    const float radius_bullet = 10;
    const float radius_player = 20;
    const float radius_rock = 25;
    const float radius_little_rock = 15;

    const int score_rock = 15;
    const int score_little_rock = 5;
    const int number_live = 3;

    sf::Texture tSpaceship, tBackground, tExplosionsTypeC, tRock, tBullet, tRockSmall, tExplosionTypeB;
    sf::RenderWindow app;
    sf::Sprite background;
    Animation sExplosion, sRock, sRock_small, sBullet, sPlayer, sPlayer_go, sExplosion_ship;
    std::list<std::shared_ptr<Entity>> entities;
    std::uniform_int_distribution<int> di{0, 5000};
    int score, players_life;
    std::shared_ptr<Player> player;
    bool player_dead;

    void collision();

    template<typename T>
    void collision_asteroid_and_bullet(T oAsteroid, T oBullet);

    void create_animation();

    void create_app();

    void create_asteroids();

    template <typename T>
    void create_little_asteroids(T &parentAsteroid);

    void create_player();

    template<typename T>
    void collision_player_and_asteroid(T oPlayer, T oAsteroid);

    void delete_explosion();

    void download_texture();

    void draw_all();

    void draw_background();

    void draw_lives();

    void draw_entity();

    void draw_score();

    bool game_over();

    template<typename T>
    bool isCollide(T firstEntity, T secondEntity);

    void moving();

    void pressKey();

public:
    Game();

    void play();
};

#endif