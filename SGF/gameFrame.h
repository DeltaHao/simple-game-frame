#pragma once

#include"gameInterface.h"


class GameFrame {
public:
	bool init(HINSTANCE);
	void run();	
	~GameFrame();
private:
	GameInterface* game = NULL;//��Ϸ

	HINSTANCE hinstance = NULL;//Ӧ��ʵ�����
	SDL_Window* pWin = NULL;//����ָ��
	SDL_Renderer* pRenderer = NULL;//��Ⱦ��ָ�� 
	TTF_Font* pDefFont = NULL;//��Ϸ��Դ

	int renderFPS(float);
};