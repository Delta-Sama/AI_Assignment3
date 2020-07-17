#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "ObjectManager.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::start()
{
	// Plane Sprite
	m_pPlaneSprite = new Plane({0.0f,0.0f,0.0f,0.0f});
	addChild(m_pPlaneSprite);

	// Player Sprite
	m_pPlayer = new Player({ 0.0f,0.0f,0.0f,0.0f });
	addChild(m_pPlayer);
	m_playerFacingRight = true;

	addChild(ObjectManager::CreateObject(OBSTACLE));
}

void PlayScene::draw()
{	
	drawDisplayList();

	if (CollisionManager::LOSCheck(m_pPlayer, m_pPlaneSprite))
		Util::DrawLine(m_pPlayer->getTransform()->position, m_pPlaneSprite->getTransform()->position);
	else
		Util::DrawLine(m_pPlayer->getTransform()->position, m_pPlaneSprite->getTransform()->position, glm::vec4(1, 0, 0, 1));

}

void PlayScene::update()
{
	updateDisplayList();
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	// handle player movement with GameController
	if (SDL_NumJoysticks() > 0)
	{
		if (EventManager::Instance().getGameController(0) != nullptr)
		{
			const auto deadZone = 10000;
			if (EventManager::Instance().getGameController(0)->LEFT_STICK_X > deadZone)
			{
				m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
				m_playerFacingRight = true;
				m_pPlayer->setAccelX(1.0f);
			}
			else if (EventManager::Instance().getGameController(0)->LEFT_STICK_X < -deadZone)
			{
				m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
				m_playerFacingRight = false;
				m_pPlayer->setAccelX(-1.0f);
			}
			else
			{
				if (m_playerFacingRight)
				{
					m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
				}
				else
				{
					m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
				}
			}

			if (EventManager::Instance().getGameController(0)->LEFT_STICK_Y > deadZone)
			{
				m_playerFacingRight == true ? m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT) : m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
				m_pPlayer->setAccelY(-1.0f);
			}
			else if (EventManager::Instance().getGameController(0)->LEFT_STICK_Y < -deadZone)
			{
				m_playerFacingRight == true ? m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT) : m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
				m_pPlayer->setAccelY(1.0f);
			}
		}
	}

	// handle player movement if no Game Controllers found
	if (SDL_NumJoysticks() < 1)
	{
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
			m_playerFacingRight = false;
			m_pPlayer->setAccelX(-1.0f);
			
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
			m_playerFacingRight = true;
			m_pPlayer->setAccelX(1.0f);
		}
		else
		{
			if (m_playerFacingRight)
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
			}
			else
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
			}
		}
		
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
		{
			m_playerFacingRight == true ? m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT) : m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
			m_pPlayer->setAccelY(-1.0f);
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
		{
			m_playerFacingRight == true ? m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT) : m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
			m_pPlayer->setAccelY(1.0f);
		}
	}
	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}