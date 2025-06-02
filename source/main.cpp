#include "engine/core/log.hpp"

#include "application/application.hpp"

#include <Windows.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	engine::logger::initialize();

	application app;
	app.run();

	return 0;
}
