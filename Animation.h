#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
    sf::Sprite sprite;
public:
    float m_frame{}, speed{};
    std::vector<sf::IntRect> frames;

    Animation() = default;

    sf::Sprite& get_sprite ();

    Animation(sf::Texture &t, int x, int y, int w, int h, int count, float Speed);

    void update();

    bool isEnd();
};

#endif