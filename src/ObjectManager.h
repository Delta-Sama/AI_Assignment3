#pragma once
#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_
#include "GameObjectType.h"
#include "Obstacle.h"

class ObjectManager
{
public:
	static DisplayObject* CreateObject(GameObjectType type);
	static void AddObjectToVector(DisplayObject* object) { m_objects.push_back(object); };
	static std::vector<Obstacle*>* GetObstacles() { return &m_obstacles; };
	static std::vector<DisplayObject*>* GetObjects() { return &m_objects; };
private:
	static std::vector<Obstacle*> m_obstacles;
	static std::vector<DisplayObject*> m_objects;
};

#endif
