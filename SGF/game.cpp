#include "game.h"
#include "sgfHelper.h"
bool Game::loadResource(HINSTANCE hinstance, SDL_Renderer*)
{
	//创建默认字体
	SDL_RWops* rwOps = getResourceData(hinstance, MAKEINTRESOURCE(IDR_FONT1), RT_FONT);
	if (!rwOps) {
		SDL_Log("Could not get font resource data: %s\n", SDL_GetError());
		return false;
	}
	pDefFont = TTF_OpenFontRW(rwOps, 1, 18);
	if (!pDefFont) {
		SDL_Log("Could not open font: %s\n", SDL_GetError());
		return false;
	}
	return true;
}
