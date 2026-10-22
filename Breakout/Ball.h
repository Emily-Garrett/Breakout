#pragma once
#include <SFML/Graphics.hpp>


class GameManager;  // forward declaration



class Ball {
public:
    Ball(sf::RenderWindow* window, GameManager* gameManager);
    ~Ball();
    void update(float dt);
    void render();
    void setVelocityMultiplier(float coeff, float duration);
    void setFireBall(float duration);
    void resetBall();

private:
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    float _baseVelocity;
    float _velocityMultiplier;
    float _currentVelocity;
    bool _isAlive;
    bool _isFireBall;
    float _timeWithPowerupEffect;
    float _hitstop;

    GameManager* _gameManager;  // Reference to the GameManager


    static constexpr float RADIUS = 10.0f;      
    static constexpr float BASE_VELOCITY = 350.0f;   // for reference.
    static constexpr float VELOCITY_STEP = 25.0f;
    static constexpr float MAX_VELOCITY = 500.0f;
};

