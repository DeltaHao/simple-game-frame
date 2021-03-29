#include"interface.h"



class Game: public GameInterface{
public:

	virtual bool init();										//初始化游戏
	virtual bool loadResource(HINSTANCE, SDL_Renderer*);		//加载游戏资源	
	virtual void processEvent(SDL_Event*);						//处理游戏事件
	virtual void update();										//更新游戏数据
	virtual void render(SDL_Window*, SDL_Renderer*);			//渲染游戏画面
	virtual ~Game();
};