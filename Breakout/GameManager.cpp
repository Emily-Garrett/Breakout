#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f), _comboCount(0), _level(0)
{
    _font.loadFromFile("font/montS.ttf");
    _masterText.setFont(_font);
    _masterText.setPosition(50, 400);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Yellow);
}

GameManager::~GameManager()
{
    if (_paddle) delete _paddle;
    if (_brickManager) delete _brickManager;
    if (_messagingSystem) delete _messagingSystem;
    if (_ball) delete _ball;
    if (_powerupManager) delete _powerupManager;
    if (_ui) delete _ui;
    if (_audio) delete _audio;
}

void GameManager::initialize()
{
    if (_paddle) delete _paddle;
    if (_brickManager) delete _brickManager;
    if (_messagingSystem) delete _messagingSystem;
    if (_ball) delete _ball;
    if (_powerupManager) delete _powerupManager;
    if (_ui) delete _ui;

    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _ball = new Ball(_window, this); 
    _powerupManager = new PowerupManager(_window, _paddle, _ball);
    _ui = new UI(_window, _lives, this);
    _audio = new AudioManager();

    // Create bricks
    int rows = 5 + _level;
    int columns = 10 + _level;
    _brickManager->createBricks(rows, columns, 800.f / columns, 150.f / rows, 50.0f / columns);
}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;

    if (_lives <= 0)
    {
        _masterText.setString("Game over.\nPress Enter to restart.");
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) { restartLevel(); }
        return;
    }
    if (_levelComplete)
    {
        _masterText.setString("Level completed.\nPress Enter to advance.");
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) { advanceLevel(); }
        return;
    }
    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        if (!_pause && _pauseHold <= 0.f)
        {
            _pause = true;
            _masterText.setString("paused.");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
        if (_pause && _pauseHold <= 0.f)
        {
            _pause = false;
            _masterText.setString("");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
    }
    if (_pause)
    {
        return;
    }

    // timer.
    _time += dt;


    if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand()%700 == 0)      // TODO parameterise
    {
        _powerupManager->spawnPowerup();
        _timeLastPowerupSpawned = _time;
    }

    // update everything 
    _paddle->update(dt);
    _ball->update(dt);
    _powerupManager->update(dt);
    _audio->clearSounds();
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);

    // TODO screen shake.
}

void GameManager::render()
{
    _paddle->render();
    _ball->render();
    _brickManager->render();
    _powerupManager->render();
    _window->draw(_masterText);
    _ui->render();
}

void GameManager::levelComplete()
{
    _levelComplete = true;
}

void GameManager::incrementCombo()
{
    _comboCount++;
    _ui->updateComboCount(_comboCount);
}

void GameManager::resetCombo()
{
    _comboCount = 0;
    _ui->updateComboCount(_comboCount);
}

int GameManager::getComboCount()
{
    return _comboCount;
}

void GameManager::restartLevel()
{
    _masterText.setString("");

    _levelComplete = false;
    _comboCount = 0;
    _lives = 3;
    _time = 0.f;
    _timeLastPowerupSpawned = 0.f;

    initialize();
}

void GameManager::advanceLevel()
{
    _level++;
    restartLevel();
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
AudioManager* GameManager::getAudio() const { return _audio; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
