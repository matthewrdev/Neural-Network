#include <GF1.h>
#include <iostream>
#include <time.h>

#include "GameSettings.h"
#include "GameInterface.h"
#include "EditorInterface.h"

#include "MemoryLeak.h"

#define GAME_BUILD
//#define EDITOR_BUILD

using std::endl;
using std::cout;

void main()
{
	srand(time(0));

	cout << GF1::GetVersion() << endl;

	gSettings.Init(800, 650, 60);

	GF1::Application* application = new GF1::Application();
	application->SetRenderWindowClientSize(gSettings.WORLD_WIDTH, gSettings.WORLD_HEIGHT);
	application->SetLogicFreqency(gSettings.FRAME_RATE);

#if defined(GAME_BUILD)

	// Create the game.
	CarDemo::GameInterface* game = new CarDemo::GameInterface();

	application->Run(*game);

	delete game;

#endif
#if defined(EDITOR_BUILD)

	// Create the polygon editor.
	CarDemo::EditorInterface* game = new CarDemo::EditorInterface();

	application->Run(*game);

	delete game;
#endif

	delete application;
	
	GF1::ReleaseAllTexture();

#ifdef _CHECK_MEM_LEAKS
	_CrtDumpMemoryLeaks();
#endif // #ifdef _CHECK_MEM_LEAKS


}
