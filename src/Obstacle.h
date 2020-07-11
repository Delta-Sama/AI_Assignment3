#pragma once
#ifndef _OBSTALE_H_
#define _OBSTALE_H_
#include "DisplayObject.h"

class Obstacle : public DisplayObject
{
public:
	Obstacle();
	~Obstacle();
	
	void draw() override;
	void update() override;
	void clean() override;

private:

};

#endif // !_OBSTALE_H_
