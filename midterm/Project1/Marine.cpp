#include "Marine.h"

Marine::Marine() : tankBullet(0)
{
	this->presentRect = { 200, 200, 50, 50 };
}

bool Marine::isCollisionOutside(SDL_Rect& targetPos) const
{
	int adjustMarinePosX = this->presentRect.x + static_cast<int>(this->presentRect.w / 2);
	int adjustMarinePosY = this->presentRect.y + static_cast<int>(this->presentRect.h / 2);

	if (adjustMarinePosX > targetPos.x - 5 && adjustMarinePosX < (targetPos.x + targetPos.w + 5)
		&& adjustMarinePosY > targetPos.y - 5 && adjustMarinePosY < (targetPos.y + targetPos.h + 5))
		return true;

	return false;
}

bool Marine::isCollisionInside(SDL_Rect& targetPos) const
{
	int adjustMarinePosX = this->presentRect.x + static_cast<int>(this->presentRect.w / 2);
	int adjustMarinePosY = this->presentRect.y + static_cast<int>(this->presentRect.h / 2);

	if (adjustMarinePosX > targetPos.x + 20 && adjustMarinePosX < (targetPos.x + targetPos.w - 20)
		&& adjustMarinePosY > targetPos.y + 10 && adjustMarinePosY < (targetPos.y + targetPos.h - 20))
		return true;

	return false;
}

bool Marine::isBackgroundCollision(SDL_Rect& targetPos) const
{

	if (this->presentRect.x > targetPos.x + 10 && this->presentRect.x < (targetPos.x + targetPos.w) - 70
		&& this->presentRect.y > targetPos.y + 10 && this->presentRect.y < (targetPos.y + targetPos.h) - 70)
		return true;

	return false;
}

SDL_Rect Marine::getPresentRect() const
{
	return this->presentRect;
}

int Marine::getTankBullet() const
{
	return this->tankBullet;
}

int Marine::getPosX() const
{
	return this->presentRect.x;
}

int Marine::getPosY() const
{
	return this->presentRect.y;
}

void Marine::SetPosX(int _posX)
{
	this->presentRect.x = _posX;
}

void Marine::SetPosY(int _posY)
{
	this->presentRect.y = _posY;
}

void Marine::setPresentRect(const SDL_Rect& _presentRect)
{
	this->presentRect.x = _presentRect.x;
	this->presentRect.y = _presentRect.y;
	this->presentRect.w = _presentRect.w;
	this->presentRect.h = _presentRect.h;
}

void Marine::setTankBullet(int _tankBullet)
{
	this->tankBullet = _tankBullet;
};