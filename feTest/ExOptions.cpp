#include "ExOptions.h"

ExOptions::Scale::DimensionPair::DimensionPair(unsigned perW, unsigned perH)
{
	if (!percentWidth || !percentHeight)
		throw std::invalid_argument("scaled percent cannot be 0");

	percentWidth = perW / 100.0;
	percentHeight = perH / 100.0;
}

ExOptions::Scale::Scale() : dimPair(100, 100), scaledRect({ 0, 0, 0, 0 })
{}

ExOptions::Scale::Scale(const DimensionPair&& dp) : dimPair(dp), scaledRect({ 0, 0, 0, 0 })
{}

ExOptions::Scale::Scale(int x_scale, int y_scale) : dimPair(x_scale, y_scale), scaledRect({ 0, 0, 0, 0 })
{}

const SDL_Rect* ExOptions::Scale::get_scaled(const SDL_Rect& orig)
{
	scaledRect.x = orig.x;
	scaledRect.y = orig.y;
	scaledRect.w = (orig.w * dimPair.percentWidth);
	scaledRect.h = (orig.h * dimPair.percentHeight);

	return &scaledRect;
}

ExOptions::Scale& ExOptions::Scale::operator=(const DimensionPair&& dp)
{
	this->dimPair = dp;
	return *this;
}
