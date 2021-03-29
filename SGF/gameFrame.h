#pragma once

#include"game.h"


class GameFrame {
public:
	bool init(HINSTANCE);
	void run();	
	~GameFrame();
private:
	Game* game = NULL;//游戏

	HINSTANCE hinstance = NULL;//应用实例句柄
	SDL_Window* pWin = NULL;//窗口指针
	SDL_Renderer* pRenderer = NULL;//渲染器指针 
	TTF_Font* pDefFont = NULL;//游戏资源

	int renderFPS(float);
};