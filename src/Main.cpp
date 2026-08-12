#include "Application.h"

int main() {
	Application* app = new Application;
	if(!app->init()) {
		delete app;
		return -1;
	}
	while(app->isRunning()) {
		app->run();
	}
	app->shutdown();
	delete app;
	return 0;
}
