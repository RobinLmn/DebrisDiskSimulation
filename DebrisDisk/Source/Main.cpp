#include "Engine/Engine.h"

int main(int argc, char** argv)
{
	DebrisDisk::FEngine& Engine = DebrisDisk::FEngine::GetEngine();
	Engine.Run();

	return 0;
}
