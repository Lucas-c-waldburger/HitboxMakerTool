#pragma once
#include "Texture.h"


namespace Sprites
{
	enum class SheetLayout { HORIZONTAL, VERTICAL };

	template <size_t NUM_CELLS, SheetLayout LAYOUT>
	class SpriteSheet
	{
	public:
		SpriteSheet() = default;
		SpriteSheet(SDL_Renderer* renderer, const std::string& imgPath);

		bool loadSheet(SDL_Renderer* renderer, const std::string& imgPath);

	private:
		Texture mTexture;
		SDL_Rect cells[NUM_CELLS];
		ExOptions exOptions;

		template <int CELL_W, int CELL_H, size_t INDEX>
		static constexpr void fillCells(SDL_Rect cells[NUM_CELLS]);
	};







	template<size_t NUM_CELLS, SheetLayout LAYOUT>
	inline SpriteSheet<NUM_CELLS, LAYOUT>::SpriteSheet(SDL_Renderer* renderer, const std::string& imgPath)
	{
		if (!mTexture.load(renderer, imgPath))
		{
			const std::string errMsg = "Error loading image from path: " + imgPath;
			throw std::exception(errMsg);
		}

		fillCells<
			(LAYOUT == SheetLayout::HORIZONTAL) ? mTexture.width() / NUM_CELLS : mTexture.width(),
			(LAYOUT == SheetLayout::VERTICAL) ? mTexture.height() / NUM_CELLS : mTexture.height(),
			0
		>(cells);
	}

	template<size_t NUM_CELLS, SheetLayout LAYOUT>
	inline bool SpriteSheet<NUM_CELLS, LAYOUT>::loadSheet(SDL_Renderer* renderer, const std::string& imgPath)
	{
		return false;
	}

	template<size_t NUM_CELLS, SheetLayout LAYOUT>
	template<int CELL_W, int CELL_H, size_t INDEX>
	inline constexpr void SpriteSheet<NUM_CELLS, LAYOUT>::fillCells(SDL_Rect cells[NUM_CELLS])
	{
		cells[INDEX] = 
		{
			(LAYOUT == SheetLayout::HORIZONTAL) ? INDEX * CELL_W : 0,
			(LAYOUT == SheetLayout::VERTICAL)   ? INDEX * CELL_H : 0,
			CELL_W,
			CELL_H
		};

		if (INDEX < NUM_CELLS - 1)
			fillCells<CELL_W, CELL_H, INDEX + 1>(cells);
	}

};

