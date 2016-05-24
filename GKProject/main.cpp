#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Includes.h"
#include "TankWindow.h"

using namespace std;

void main(void)
{
#ifdef _DEBUG
	int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	tmpFlag |= _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF;  // Check heap alloc and dump mem leaks at exit
	_CrtSetDbgFlag(tmpFlag);

#endif
	TankWindow window;
	try {
		window.renderWindow(820, 760, "Light Tanks");
	}
	catch (p3d::GLEWInitError & e) {
#ifdef _DEBUG
		cout << e.what();
#endif
		MessageBox(NULL, "Cannot lauch the game!", "ERROR", NULL);
	}
}

