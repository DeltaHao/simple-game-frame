#include"interface.h"



class Game: public GameInterface{
public:

	virtual bool init();										//��ʼ����Ϸ
	virtual bool loadResource(HINSTANCE, SDL_Renderer*);		//������Ϸ��Դ	
	virtual void processEvent(SDL_Event*);						//������Ϸ�¼�
	virtual void update();										//������Ϸ����
	virtual void render(SDL_Window*, SDL_Renderer*);			//��Ⱦ��Ϸ����
	virtual ~Game();
};