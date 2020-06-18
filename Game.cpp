#include "Game.h"

Game::Game() : score(0), players_life(number_live), player_dead(false) {
    download_texture();
    create_app();
    create_animation();
    for (int i = 0; i < 15; i++) {
        create_asteroids();
    }
    create_player();
}

void Game::collision() {
    for (auto &a:entities) {
        for (auto &b:entities) {
            if (a->get_name() == constants::name_Asteroid && b->get_name() == constants::name_Bullet) {
                if (isCollide(a, b)) {
                    collision_asteroid_and_bullet(a, b);
                }
            }

            if (a->get_name() == constants::name_Player && b->get_name() == constants::name_Asteroid) {
                if (isCollide(a, b)) {
                    collision_player_and_asteroid(a, b);
                    return;
                }
            }

        }
    }
}

template<typename T>
void Game::collision_asteroid_and_bullet(T oAsteroid, T oBullet) {
    oAsteroid->life = false;
    oBullet->life = false;

    if (oAsteroid->R != radius_little_rock) {
        score += score_rock;
    } else {
        score += score_little_rock;
    }

    auto e = std::make_shared<Entity>(sExplosion, static_cast<int> (oAsteroid->x), static_cast<int> (oAsteroid->y),
                                      constants::name_Explosion);
    entities.push_back(e);


    // из одного большого появляется 4 малениких
    for (int i = 0; i < 2; i++) {
        if (oAsteroid->R == radius_little_rock) {
            continue;
        }

        create_little_asteroids(oAsteroid);
    }
}

void Game::create_animation() {
    Animation s1(tExplosionsTypeC, 0, 0, 256, 256, 48, 0.5);
    sExplosion = s1;
    Animation s2(tRock, 0, 0, 64, 64, 16, 0.2);
    sRock = s2;
    Animation s3(tRockSmall, 0, 0, 64, 64, 16, 0.2);
    sRock_small = s3;
    Animation s4(tBullet, 0, 0, 32, 64, 16, 0.8);
    sBullet = s4;
    Animation s5(tSpaceship, 40, 0, 40, 40, 1, 0);
    sPlayer = s5;
    Animation s6(tSpaceship, 40, 40, 40, 40, 1, 0);
    sPlayer_go = s6;
    Animation s7(tExplosionTypeB, 0, 0, 192, 192, 64, 0.5);
    sExplosion_ship = s7;
}

void Game::create_app() {
    app.create(sf::VideoMode(constants::width_app, constants::height_app), "Asteroids!");
    app.setFramerateLimit(60);

}

void Game::create_asteroids() {
    auto a = std::make_shared<Asteroid>(sRock, 0,
                                        di(constants::dre) % constants::height_app,
                                        constants::name_Asteroid,
                                        static_cast<float> (di(constants::dre) % 360),
                                        radius_rock);
    entities.emplace_back(a);
}

template<typename T>
void Game::create_little_asteroids(T &parentAsteroid) {
    auto e1 = std::make_shared<Asteroid>(sRock_small,
                                         static_cast<int> (parentAsteroid->x),
                                         static_cast<int> (parentAsteroid->y),
                                         constants::name_Asteroid,
                                         static_cast<float> (di(constants::dre) % 360),
                                         radius_little_rock);
    entities.push_back(e1);
}

void Game::create_player() {
    player = std::make_shared<Player>(sPlayer, constants::width_app / 2, constants::height_app / 2,
                                      constants::name_Player, 0, radius_player);
    entities.emplace_back(player);
}

template<typename T>
void Game::collision_player_and_asteroid(T oPlayer, T oAsteroid) {
    players_life--;

    if (players_life <= 0) {
        player_dead = true;
    }

    oPlayer->life = false;
    oAsteroid->life = false;

    auto e = std::make_shared<Entity>(sExplosion_ship, static_cast<int> (oPlayer->x), static_cast<int> (oPlayer->y),
                                      constants::name_Explosion);
    entities.emplace_back(e);

    create_player();
    player->dx = 0;
    player->dy = 0;
}

void Game::delete_explosion() {
    for (const auto &e:entities) {
        if (e->get_name() == constants::name_Explosion) {
            if (e->anim.isEnd()) {
                e->life = false;
            }
        }
    }
}

void Game::download_texture() {
    tSpaceship.loadFromFile("images/spaceship.png");
    tBackground.loadFromFile("images/background.jpg");
    tExplosionsTypeC.loadFromFile("images/explosions/type_C.png");
    tRock.loadFromFile("images/rock.png");
    tBullet.loadFromFile("images/fire_blue.png");
    tRockSmall.loadFromFile("images/rock_small.png");
    tExplosionTypeB.loadFromFile("images/explosions/type_B.png");

    tSpaceship.setSmooth(true);
    tBackground.setSmooth(true);


    background.setTexture(tBackground);
}

void Game::draw_all() {
    draw_background();
    draw_lives();
    draw_score();
    draw_entity();
    app.display();
}

void Game::draw_background() {
    app.draw(background);
}

void Game::draw_lives() {
    sf::Font font;
    font.loadFromFile("CyrilicOld.ttf");
    sf::Text text_lives("", font, 20);
    text_lives.setStyle(sf::Text::Bold);
    std::stringstream str_lives;
    str_lives << players_life;
    text_lives.setString("You have lives: " + str_lives.str());
    text_lives.setPosition(30, 20);
    app.draw(text_lives);
}

void Game::draw_entity() {
    for (const auto &i:entities) {
        i->draw(app);
    }
}

void Game::draw_score() {
    sf::Font font_score;
    font_score.loadFromFile("CyrilicOld.ttf");
    sf::Text text_score("", font_score, 20);
    text_score.setStyle(sf::Text::Bold);
    std::stringstream str_score;
    str_score << score;
    text_score.setString("Score: " + str_score.str());
    text_score.setPosition(800, 20);
    app.draw(text_score);
}

bool Game::game_over() {
    if (player_dead) {
        draw_background();
        sf::Font font;
        font.loadFromFile("CyrilicOld.ttf");
        sf::Text text("", font, 40);
        text.setStyle(sf::Text::Bold);
        std::stringstream str_score;
        str_score << score;
        text.setString("Lives are over.\n"
                       "You lost.\n"
                       "Your score: " + str_score.str());
        text.setPosition(300, 100);
        app.draw(text);
        app.display();
    }
    return player_dead;
}

template<typename T>
bool Game::isCollide(T firstEntity, T secondEntity) {
    return (secondEntity->x - firstEntity->x) * (secondEntity->x - firstEntity->x) +
           (secondEntity->y - firstEntity->y) * (secondEntity->y - firstEntity->y) <
           (firstEntity->R + secondEntity->R) * (firstEntity->R + secondEntity->R);
}

void Game::moving() {
    for (auto i = entities.begin(); i != entities.end();) {
        auto e = std::make_shared<Entity>();
        e = *i;

        e->update();
        e->anim.update();

        if (!e->life) {
            i = entities.erase(i);
        } else {
            i++;
        }
    }

//        включает "огоньки" на карабле при движении
    if (player->thrust) {
        player->anim = sPlayer_go;
    } else {
        player->anim = sPlayer;
    }

}

void Game::play() {
    while (app.isOpen()) {
        pressKey();
        collision();
        delete_explosion();

        // в случайный момент времни создаём астероид
        if (di(constants::dre) % 150 == 0) {
            create_asteroids();
        }

        moving();

        // if player is dead
        if (!game_over()) {
            draw_all();
        }
    }
}

void Game::pressKey() {
    sf::Event event{};

    // if closed app
    while (app.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            app.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        auto b = std::make_shared<Bullet>(sBullet, static_cast<int> (player->x), static_cast<int> (player->y),
                                          constants::name_Bullet, player->angle, radius_bullet);

        entities.push_back(b);
        entities.emplace_back(b);
    }

    player->thrust = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player->angle += speed_rotation_spaceship;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player->angle -= speed_rotation_spaceship;

}