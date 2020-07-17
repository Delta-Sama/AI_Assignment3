#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "PlayerAnimationState.h"
#include "Sprite.h"

class Player final : public Sprite
{
public:
	Player(SDL_FRect dst);
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	void setAccelX(double acc);
	void setAccelY(double acc);

	void move();
	
	// setters
	void setAnimationState(PlayerAnimationState new_state);

private:
	void m_buildAnimations();

	PlayerAnimationState m_currentAnimationState;
};

#endif /* defined (__PLAYER__) */