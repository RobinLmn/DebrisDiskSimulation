#include "Engine/Engine.h"

int main(int argc, char** argv)
{
	DebrisDisk::Engine& Engine = DebrisDisk::Engine::GetEngine();
	Engine.Run();

	return 0;
}
