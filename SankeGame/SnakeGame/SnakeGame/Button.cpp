#include "Button.h"
Button::Button(const SDL_Rect& _srcPos, const SDL_Rect& _renderPos, SDL_Texture* _buttonImage) : buttonImage(_buttonImage)
{
	setSrcPos(_srcPos);
	setRenderPos(_renderPos);
}

bool Button::isMouseClickInRange(const int & targetPosx, const int & targetPosY)
{
	if (targetPosx >= this->renderPos.x && targetPosx <= this->renderPos.x + this->renderPos.w
		&& targetPosY >= this->renderPos.y && targetPosY <= this->renderPos.y + this->renderPos.h)
		return true;

	return false;
}

void Button::setSrcPos(const SDL_Rect& _srcPos)
{
	this->srcPos.x = _srcPos.x;
	this->srcPos.y = _srcPos.y;
	this->srcPos.w = _srcPos.w;
	this->srcPos.h = _srcPos.h;
}

void Button::setRenderPos(const SDL_Rect& _renderPos)
{
	this->renderPos.x = _renderPos.x;
	this->renderPos.y = _renderPos.y;
	this->renderPos.w= _renderPos.w;
	this->renderPos.h = _renderPos.h;
}

SDL_Rect& Button::getSrcPos()
{
	return this->srcPos;
}

SDL_Rect& Button::getRenderPos()
{
	return this->renderPos;
}

SDL_Texture* Button::getButtonImage() const
{
	return this->buttonImage;
}

Button::~Button()
{
	SDL_DestroyTexture(this->buttonImage);
}