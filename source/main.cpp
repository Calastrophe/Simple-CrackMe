#include <iostream>
#include "window.h"

int main()
{
	std::cout << "Creating window...\n";

	Window * pWindow = new Window();
	
	bool running = true;
	while (running)
	{
		if (!pWindow->ProcessMessages())
		{
			std::cout << "Closing window...\n";
			running = false;
		}

		// Render

		Sleep(10);

	}
	delete pWindow;
	return 0;
}
