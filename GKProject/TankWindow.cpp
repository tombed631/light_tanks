#include "TankWindow.h"
#include "3Dft\GLExceptions.h"
using namespace sf;
using namespace std;

void TankWindow::renderWindow(int height, int width, string name)
{

	RenderWindow window(sf::VideoMode(height, width, 64), name,sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings(24));
	window.setFramerateLimit(100);

	//initialize glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		throw p3d::GLEWInitError();	//throw ex and shut down the game or remove 3d from game XD
	}

	try {
		Menu().showMenu(window);
	}
	catch (p3d::ShaderCompileError & e) {
	#ifdef _DEBUG
		cout << e.what() << endl;
	#endif
		MessageBox(NULL, "Cannot compile shaders!", "ERROR", NULL);
	}
	catch (p3d::LoadModelError & e) {
	#ifdef _DEBUG
		cout << e.what() << endl;
	#endif
		MessageBox(NULL, "Cannot load models!", "ERROR", NULL);
	}
	catch (LoadFontError & e) {
	#ifdef _DEBUG
		cout << e.what() << endl;
	#endif
		MessageBox(NULL, "Cannot load font!", "ERROR", NULL);
	}
}

