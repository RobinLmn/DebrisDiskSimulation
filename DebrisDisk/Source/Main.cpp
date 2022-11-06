#include "Engine/Engine.h"

int main()
{
	DebrisDisk::FEngine& Engine = DebrisDisk::FEngine::GetEngine();
	Engine.Run();
}
