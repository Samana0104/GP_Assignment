#pragma once

#include "SDL.h"

class Marine
{
private:
	SDL_Rect presentRect;
	int tankBullet;
public:
	explicit Marine();

	bool isCollisionOutside(SDL_Rect& targetPos) const;
	bool isCollisionInside(SDL_Rect& targetPos) const;

	bool isBackgroundCollision(SDL_Rect& targetPos) const;
	SDL_Rect getPresentRect() const;
	int getTankBullet() const;
	int getPosX() const;
	int getPosY() const;
	void SetPosX(int _posX);
	void SetPosY(int _posY);
	void setPresentRect(const SDL_Rect& _presentRect);
	void setTankBullet(int _tankBullet);
};