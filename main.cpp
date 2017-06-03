#include <stdlib.h>
#include <stdio.h>

#include "Engine.h"

int main(int argc, char* argv[])
{
	// Startup subsystems
	if (!Engine::GetInstance()->Startup())
		return -1;

	// Run() contains main loop
	Engine::GetInstance()->Run();
	
	// Shutdown subsystems
	Engine::GetInstance()->Shutdown();

return 0;
}