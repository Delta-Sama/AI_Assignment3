#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"

#include <vector>

class DebugMode;

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	void checkCollision();

	Player* GetPlayer() { return m_pPlayer; }
	Plane* GetPlane() { return m_pPlaneSprite; }
private:
	glm::vec2 m_mousePosition;

	//std::vector<Enemy*>

	DebugMode* debugger;
	
	Plane* m_pPlaneSprite;
	Player* m_pPlayer;
	bool m_playerFacingRight;
};

class DebugMode
{
public:
	DebugMode(PlayScene* scene);
	~DebugMode() = default;

	PlayScene* m_playScene;
	
	void SetMode(bool newMode) { m_mode = newMode; }
	bool GetMode() { return m_mode; }
	void Draw();
	
private:
	bool m_mode;
	
};

#endif /* defined (__PLAY_SCENE__) */