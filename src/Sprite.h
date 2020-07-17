#pragma once
#ifndef __SPRITE__
#define __SPRITE__

#include "DisplayObject.h"
#include "Animation.h"
#include <unordered_map>
#include "SpriteSheet.h"
#include <SDL_Image/include/SDL_image.h>

class Sprite : public DisplayObject
{
public:
	Sprite(SDL_FRect dst);
	virtual ~Sprite();
	
	// Life Cycle Functions
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

	// getters
	SpriteSheet* getSpriteSheet();
	Animation& getAnimation(const std::string& name);
	
	// setters
	void setSpriteSheet(SpriteSheet* sprite_sheet);
	void setAnimation(const Animation& animation);

	SDL_FRect* getDst() { return &m_dst; }
private:
	// private utility functions
	bool m_animationExists(const std::string& id);

	SpriteSheet* m_pSpriteSheet;

	SDL_FRect m_dst;

	std::unordered_map<std::string, Animation> m_pAnimations;
};

#endif /* defined (__SPRITE__) */