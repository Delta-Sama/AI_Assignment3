#include "Player.h"

#include <algorithm>

#include "TextureManager.h"

Player::Player(SDL_FRect dst) : Sprite(dst), m_currentAnimationState(PLAYER_IDLE_RIGHT)
{
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png", 
		"spritesheet");

	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("spritesheet"));
	
	// set frame width
	setWidth(53);

	// set frame height
	setHeight(58);

	getTransform()->position = glm::vec2(150.0f, 500.0f);
	
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->maxSpeed = 4.0f;
	getRigidBody()->isColliding = false;
	setType(PLAYER);

	m_buildAnimations();
}

Player::~Player()
= default;

void Player::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the player according to animation state
	switch(m_currentAnimationState)
	{
	case PLAYER_IDLE_RIGHT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("idle"),
			x, y, 0.12f, 0, 255, true);
		break;
	case PLAYER_IDLE_LEFT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("idle"),
			x, y, 0.12f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_RUN_RIGHT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("run"),
			x, y, 0.25f, 0, 255, true);
		break;
	case PLAYER_RUN_LEFT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("run"),
			x, y, 0.25f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	default:
		break;
	}
	
}

void Player::update()
{
	move();
}

void Player::clean()
{
}

void Player::setAccelX(double acc) { getRigidBody()->acceleration.x = acc; }
void Player::setAccelY(double acc) { getRigidBody()->acceleration.y = acc; }

void Player::move()
{
	// X axis
	
	getRigidBody()->velocity.x += getRigidBody()->acceleration.x;
	getRigidBody()->velocity.x *= 0.9;
	getRigidBody()->velocity.x = std::min(std::max(getRigidBody()->velocity.x, -getRigidBody()->maxSpeed), (getRigidBody()->maxSpeed));

	// Y axis
	getRigidBody()->velocity.y += getRigidBody()->acceleration.y;
	getRigidBody()->velocity.y *= 0.9;
	getRigidBody()->velocity.y = std::min(std::max(getRigidBody()->velocity.y, -getRigidBody()->maxSpeed), (getRigidBody()->maxSpeed));

	getTransform()->position.x += (int)this->getRigidBody()->velocity.x;
	getTransform()->position.y += (int)this->getRigidBody()->velocity.y;
	
	getRigidBody()->acceleration.x = getRigidBody()->acceleration.y = 0.0;

	if (getTransform()->position.x < 0 + getWidth() / 2.0)
	{
		getTransform()->position.x = 0 + getWidth() / 2.0;
	}
	else if (getTransform()->position.x > 800 - getWidth() / 2.0)
	{
		getTransform()->position.x = 800 - getWidth() / 2.0;
	}
	if (getTransform()->position.y < 0 + getHeight() / 2.0)
	{
		getTransform()->position.y = 0 + getHeight() / 2.0;
	}
	else if (getTransform()->position.y > 600 - getHeight() / 2.0)
	{
		getTransform()->position.y = 600 - getHeight() / 2.0;
	}
}

void Player::setAnimationState(const PlayerAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void Player::m_buildAnimations()
{
	Animation idleAnimation = Animation();

	idleAnimation.name = "idle";
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-0"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-1"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-2"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-3"));

	setAnimation(idleAnimation);

	Animation runAnimation = Animation();

	runAnimation.name = "run";
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-0"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-1"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-2"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-3"));

	setAnimation(runAnimation);
}
