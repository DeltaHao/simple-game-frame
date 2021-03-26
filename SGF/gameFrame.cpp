#include "gameFrame.h"
#include "sgfhelper.h"

bool GameFrame::init(HINSTANCE hin)
{
	hinstance = hin;

	bool ret;
	//��ʼ��SDL
	ret = SDL_Init(SDL_INIT_EVERYTHING);
	if (ret) {
		SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
		return false;
	}

	//��ʼ��TTF
	ret = TTF_Init();
	if (ret) {
		SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
		return false;
	}

	//��ʼ����Ϸ
	game = new GameInterface();
	ret = game->init();
	if (!ret) {
		SDL_Log("Unable to initialize game\n");
		return false;
	}

	//��������
	pWin = SDL_CreateWindow(game->title.data(), 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		game->w, game->h,
		(game->isResizable) ? SDL_WINDOW_RESIZABLE : 0);
	if (!pWin) {
		SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
		return false;
	}

	//������Ⱦ��
	pRenderer = SDL_CreateRenderer(pWin, -1, SDL_RENDERER_ACCELERATED);
	if (!pRenderer) {
		SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
		return false;
	}

	//����Ĭ������
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

	//������Դ
	ret = game->loadResource();
	if (!ret) {
		SDL_Log("Unable to load resource");
		return false;
	}
}

void GameFrame::run()
{
	int fps = DEFAULT_FPS;
	if (game->FPS > 0) {
		fps = game->FPS;
	}

	int quit = 0;
	SDL_Event evt;

	Uint64 nFrequency, nPrevCounter, nCurrCounter, nElapsedCounter;
	float elapsed = 0.0f, lag = 0.0f, frameMS = 1000.0f / fps;

	nFrequency = SDL_GetPerformanceFrequency();
	nPrevCounter = SDL_GetPerformanceCounter();

	while (!quit) {
		if (SDL_PollEvent(&evt)) {
			if (evt.type == SDL_QUIT) {
				quit = 1;
			}
			else {
				game->processEvent(&evt);
			}
		}
		else {
			nCurrCounter = SDL_GetPerformanceCounter();
			nElapsedCounter = nCurrCounter - nPrevCounter;
			nPrevCounter = nCurrCounter;
			//ǰ����֡�ĺ�ʱ(ms)
			elapsed = (nElapsedCounter * 1000.0f) / nFrequency;
			lag += elapsed;			
			//������Ϸ
			while (lag >= frameMS) {
				game->update();
				lag -= frameMS;
			}
			//�������
			SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
			SDL_RenderClear(pRenderer);
			//��Ⱦͼ��
			game->render();
			//��Ⱦ֡��	 
			renderFPS(elapsed);
			//��ת����
			SDL_RenderPresent(pRenderer);
		}
	}
	
}

int GameFrame::renderFPS(float elapsed)
{
	static float _totalTime = 0;
	static int _fps = 0;
	static int _fpsCount = 0;

	_totalTime += elapsed;

	if (_totalTime >= 1000.0f)
	{
		_totalTime -= 1000.0f;
		_fps = _fpsCount;

		_fpsCount = 1;
	}
	else
	{
		++_fpsCount;
	}


	//�������ִ�С
	char fpsText[256] = { 0 };
	sprintf_s(fpsText, 255, "FPS: %d", _fps);
	SDL_Rect dst = { 0, 0, 100, 21 };
	int ret = TTF_SizeText(pDefFont, fpsText, &(dst.w), &(dst.h));
	if (ret) {
		SDL_Log("get text size failed: %s\n", TTF_GetError());
	}


	//��Ⱦ����
	SDL_Color color = { 255, 255, 255, 255 };
	if (system) {
		SDL_Surface* surf = TTF_RenderText_Blended(pDefFont, fpsText, color);
		if (surf) {
			SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer, surf);
			if (texture) {
				SDL_RenderCopy(pRenderer, texture, NULL, &dst);
				SDL_DestroyTexture(texture);
			}
			SDL_FreeSurface(surf);
		}
	}

	return 0;
}

GameFrame::~GameFrame()
{
	if (pRenderer) {
		SDL_DestroyRenderer(pRenderer);
	}
	if (pWin) {
		SDL_DestroyWindow(pWin);
	}
	SDL_Quit();
	SDL_Quit();
}
