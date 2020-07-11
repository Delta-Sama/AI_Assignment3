#include "ObjectManager.h"

std::vector<DisplayObject*> ObjectManager::m_objects;
std::vector<Obstacle*> ObjectManager::m_obstacles;

DisplayObject* ObjectManager::CreateObject(GameObjectType type)
{
	switch (type)
	{
	case OBSTACLE:
		{
			m_obstacles.push_back(new Obstacle());
			m_objects.push_back(m_obstacles.back());
			return m_obstacles.back();
			break;
		}
	default:
		return nullptr;
		break;
	}
}
