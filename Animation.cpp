#include "Animation.h"

Animation::Animation(sf::Texture &t, int x, int y, int w, int h, int count, float Speed) :
        m_frame(0), speed(Speed) {

    for (int i = 0; i < count; i++) {
        frames.emplace_back(x + i * w, y, w, h);
    }

    sprite.setTexture(t);
    sprite.setOrigin(static_cast<float> (w) / 2, static_cast<float> (h) / 2);
    sprite.setTextureRect(frames[0]);
}

sf::Sprite &Animation::get_sprite() {
    return sprite;
}

bool Animation::isEnd() {
    return m_frame + speed >= frames.size();
}

void Animation::update() {
    m_frame += speed;
    auto n = frames.size();
    if (m_frame >= static_cast<float> (n)) {
        m_frame -= static_cast<float> (n);
    }
    if (n > 0) sprite.setTextureRect(frames[static_cast<int>(m_frame)]);
}
