#include "Ball.h"
#include "GameManager.h" // avoid cicular dependencies

Ball::Ball(sf::RenderWindow* window, GameManager* gameManager)
    : _window(window), _baseVelocity(BASE_VELOCITY), _currentVelocity(BASE_VELOCITY), _velocityMultiplier(1.f), _gameManager(gameManager),
    _timeWithPowerupEffect(0.f), _isFireBall(false), _isAlive(true), _direction({1,1})
{
    _sprite.setRadius(RADIUS);
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition(0, 300);
}

Ball::~Ball()
{
}

void Ball::update(float dt)
{
    // check for powerup, tick down or correct
    if (_timeWithPowerupEffect > 0.f)
    {
        _timeWithPowerupEffect -= dt;
    }
    else
    {
        if (_currentVelocity != _baseVelocity)
        {
            _velocityMultiplier = 1.f;
            _currentVelocity = _baseVelocity;   // reset speed.
        }
        else
        {
            setFireBall(0);    // disable fireball
            _sprite.setFillColor(sf::Color::Cyan);  // back to normal colour.
        }        
    }

    // Fireball effect
    if (_isFireBall)
    {
        // Flickering effect
        int flicker = rand() % 50 + 205; // Random value between 205 and 255
        _sprite.setFillColor(sf::Color(flicker, flicker / 2, 0)); // Orange flickering color
    }

    // Update position with a subtle floating-point error
    _sprite.move(_direction * _currentVelocity * dt);

    // check bounds and bounce
    sf::Vector2f position = _sprite.getPosition();
    sf::Vector2u windowDimensions = _window->getSize();

    // bounce on walls
    if ((position.x >= windowDimensions.x - 2 * RADIUS && _direction.x > 0) || (position.x <= 0 && _direction.x < 0))
    {
        _direction.x *= -1;
    }

    // bounce on ceiling
    if (position.y <= 0 && _direction.y < 0)
    {
        _direction.y *= -1;
    }

    // lose life bounce
    if (position.y > windowDimensions.y)
    {
        resetBall();
    }

    // collision with paddle
    if (_sprite.getGlobalBounds().intersects(_gameManager->getPaddle()->getBounds()))
    {
        if (_gameManager->getPaddle()->canParry())
        {
            _direction.y *= -1; // Bounce vertically

            float paddlePositionProportion = (_sprite.getPosition().x - _gameManager->getPaddle()->getBounds().left) / _gameManager->getPaddle()->getBounds().width;
            _direction.x = paddlePositionProportion * 2.0f - 1.0f;

            // Adjust position to avoid getting stuck inside the paddle
            _sprite.setPosition(_sprite.getPosition().x, _gameManager->getPaddle()->getBounds().top - 2 * RADIUS);

            // increase speed step
            if (_baseVelocity < MAX_VELOCITY)
            {
                _baseVelocity += VELOCITY_STEP;
                _currentVelocity = _baseVelocity * _velocityMultiplier;
            }

            _gameManager->incrementCombo();
            _gameManager->getAudio()->PlaySound(AudioManager::SoundID::Parry);
        }
        else
        {
            resetBall();
        }
    }

    // collision with bricks
    int collisionResponse = _gameManager->getBrickManager()->checkCollision(_sprite, _direction);
    if (_isFireBall) return; // no collisisons when in fireBall mode.
    if (collisionResponse == 1)
    {
        _direction.x *= -1; // Bounce horizontally
    }
    else if (collisionResponse == 2)
    {
        _direction.y *= -1; // Bounce vertically
    }
}

void Ball::render()
{
    _window->draw(_sprite);
}

void Ball::setVelocityMultiplier(float coeff, float duration)
{
    _velocityMultiplier = coeff;
    _timeWithPowerupEffect = duration;

    _currentVelocity = _baseVelocity * _velocityMultiplier;
}

void Ball::setFireBall(float duration)
{
    if (duration) 
    {
        _isFireBall = true;
        _timeWithPowerupEffect = duration;        
        return;
    }
    _isFireBall = false;
    _timeWithPowerupEffect = 0.f;    
}

void Ball::resetBall()
{
    _sprite.setPosition(0, 300);
    _direction = { 1, 1 };
    _gameManager->loseLife();
    _baseVelocity = BASE_VELOCITY;
    _currentVelocity = _baseVelocity * _velocityMultiplier;
    _gameManager->resetCombo();
}
