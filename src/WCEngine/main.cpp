#include "Application.h"
#include <iostream>

int main( int numArguments, char** arguments )
{
	if ( App.Initialize() )
	{
		// 100 steps every second. It is easier to calculate on then say, 30
		App.SetPhysicsFPS( 100.0f );
		App.Run();
		return EXIT_SUCCESS;
	}
	else
	{
		std::cerr << "Failed to init app" << std::endl;
		return EXIT_FAILURE;
	}
}
