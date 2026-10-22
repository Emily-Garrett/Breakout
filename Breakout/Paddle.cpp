#include "Paddle.h"
#include <iostream>
#include "PaddleIdle.h"

Paddle::Paddle(sf::RenderWindow* window)
    : _window(window), _width(PADDLE_WIDTH), _timeInNewSize(0.0f), _isAlive(true), _hitstop(0.f)
{
    setState(new PaddleIdle());
    _sprite.setPosition((window->getSize().x - _width) / 2.0f, window->getSize().y - 50.0f);
    _sprite.setSize(sf::Vector2f(_width, PADDLE_HEIGHT));
}

Paddle::~Paddle()
{
}

void Paddle::moveLeft(float speed, float dt)
{
    _sprite.move(sf::Vector2f(-dt * speed, 0));
}

void Paddle::moveRight(float speed, float dt)
{
    _sprite.move(sf::Vector2f(dt * speed, 0));
}

void Paddle::update(float dt)
{
    if (_hitstop > 0)
    {
        _hitstop -= dt;

        if (_hitstop <= 0)
        {
            setColour(_hitflashPrevColour);
        }

        return;
    }

    if (_timeInNewSize > 0)
    {
        _timeInNewSize -= dt;
    }
    else
    {
        setWidth(1.0f, 0.0f); // Reset to default width after duration
    }

    if (_state)
    {
        _state->OnUpdate(this, dt);
    }

    forceStageBounds();
}

void Paddle::render()
{
    _window->draw(_sprite);
}

sf::FloatRect Paddle::getBounds() const
{
    return _sprite.getGlobalBounds();
}

// update width by SF of coeff. 
// ensure centre remains consistent.
void Paddle::setWidth(float coeff, float duration)
{
    float prevWidth = _width;
    _width = coeff * PADDLE_WIDTH;
    _sprite.setSize(sf::Vector2f(_width, _sprite.getSize().y));
    _timeInNewSize = duration;
    float newX = _sprite.getPosition().x - ((_width - prevWidth) / 2.f);
    _sprite.setPosition(newX, _sprite.getPosition().y);
}

void Paddle::setState(PaddleState* newState)
{
    if (_state)
    {
        _state->OnExit(this);
        delete _state;
    }

    if (!newState)
    {
        _state = nullptr;
        return;
    }

    _state = newState;
    _state->OnEnter(this);
}

void Paddle::forceStageBounds()
{
    if (_sprite.getPosition().x < 0)
    {
        _sprite.setPosition(0, _sprite.getPosition().y);
    }

    if (_sprite.getPosition().x > _window->getSize().x - _width)
    {
        _sprite.setPosition(_window->getSize().x - _width, _sprite.getPosition().y);
    }
}

void Paddle::setCanParry(bool canParry)
{
    _canParry = canParry;
}

bool Paddle::canParry()
{
    return _canParry;
}

void Paddle::setColour(sf::Color colour)
{
    _sprite.setFillColor(colour);
}

void Paddle::setHitstop(float hitstop)
{
    _hitstop = hitstop;
}

void Paddle::setHitflash(sf::Color colour)
{
    _hitflashPrevColour = _sprite.getFillColor();
    setColour(colour);
}
