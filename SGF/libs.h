#pragma once

// ¡¥Ω”“¿¿µø‚

#pragma comment(lib, "Setupapi.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Imm32.lib")
#pragma comment(lib, "Version.lib")

#ifdef _DEBUG
#pragma comment(lib, ".\\3rdParty\\SDL2\\lib\\Debug\\MTd\\SDL2d.lib")
#pragma comment(lib, ".\\3rdParty\\SDL2\\lib\\Debug\\MTd\\SDL2maind.lib")
#pragma comment(lib, ".\\3rdParty\\SDL2_ttf\\lib\\Debug\\MTd\\SDL2_ttf.lib")
#pragma comment(lib, ".\\3rdParty\\SDL2_image\\lib\\Debug\\MTd\\SDL2_image.lib")
#pragma comment(lib, ".\\3rdParty\\SDL2_mixer\\lib\\Debug\\MTd\\SDL2_mixer.lib")
#else
#pragma comment(lib, ".\\3rdParty\\SDL2\\lib\\Release\\MT\\SDL2.lib")
#pragma comment(lib, ".\\3rdParty\\SDL2\\lib\\Release\\MT\\SDL2main.lib")
#pragma comment(lib, ".\\3rdParty\\SDL2_ttf\\lib\\Release\\MT\\SDL2_ttf.lib")
#pragma comment(lib, ".\\3rdParty\\SDL2_image\\lib\\Release\\MT\\SDL2_image.lib")
#pragma comment(lib, ".\\3rdParty\\SDL2_mixer\\lib\\Release\\MT\\SDL2_mixer.lib")
#endif