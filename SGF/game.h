/*
 �ṩ����Ϸ�����ߵĽӿ�

 ������ͨ��ʵ������ӿ���ʹ����Ϸ���
*/

#pragma once
#include<Windows.h>
#include<iostream>

#include"SDL.h"
#include"SDL_ttf.h"
#include"SDL_image.h"
#include"SDL_mixer.h"
#include"resource.h"

const std::string APP_WIN_NAME = "SGFWin";
const int DEFAULT_FPS = 60;
const int DEFAULT_WINDOW_WIDTH = 800;
const int DEFAULT_WINDOW_HEIGHT = 600;

class Game{
public:
	std::string  title = APP_WIN_NAME;							//��Ϸ����
	unsigned int w = DEFAULT_WINDOW_WIDTH;
	unsigned int h = DEFAULT_WINDOW_HEIGHT;						//���ڴ�С
	unsigned int FPS = DEFAULT_FPS;								//����֡��
	bool isResizable = 0;										//���ڴ�С�Ƿ�ɵ���

	
	virtual ~Game() {};
	virtual int init() { return 1; };							//��ʼ����Ϸ
	virtual int loadResource(SDL_Renderer*) { return 1; };		//������Ϸ��Դ
	virtual void processEvent(SDL_Event*) {};					//������Ϸ�¼�
	virtual void update() {};									//������Ϸ����
	virtual void render(SDL_Window*, SDL_Renderer*) {};			//��Ⱦ��Ϸ����
};