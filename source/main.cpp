#include "engine/core/log.hpp"
#include "application/application.hpp"

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
	int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else
	int main(int argc, char* argv[])
#endif
{
	engine::logger::initialize();

	application app;
	app.run();

	return 0;
}
