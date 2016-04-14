#include "Includes.h"
#include "TankWindow.h"

using namespace std;

void main(void)
{
	
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

