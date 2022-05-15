#pragma once

#include "SDL.h"

class Button
{
private:
	SDL_Rect srcPos, renderPos;
	SDL_Texture* buttonImage;
public:
	explicit Button(const SDL_Rect& _srcPos, const SDL_Rect& _renderPos, SDL_Texture* _buttonImage);
	~Button();

	bool isMouseClickInRange(const int& targetPosx, const int& targetPosY);
	
	void setSrcPos(const SDL_Rect& _srcPos);
	void setRenderPos(const SDL_Rect& _renderPos);

	SDL_Rect& getSrcPos();
	SDL_Rect& getRenderPos();
	SDL_Texture* getButtonImage() const;
};