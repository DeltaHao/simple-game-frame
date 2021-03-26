#include <Windows.h>
#include "libs.h"
#include "gameFrame.h"


int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	GameFrame* gameFrame = new GameFrame();
	if (gameFrame->init(hInstance)) {
		gameFrame->run();
	}	
	delete gameFrame;
	return 0;
}