/*
* In Visual Studio 2019/2022 you must set your Configuration Properties > C/C++ > General > Additional Include Directories with either:
* a static include (ie: 'C:\Users\1234\source\repos\$(SolutionName | ProjectName)\include') to the SDL headers
* or set a dynamic include path (ie: '$(SolutionDir)$(ProjectName)\include') to the SDL headers
*/
#include "SDL2-2.32.10/SDL.h"

/*
* The issue I found with your library *.lib include was you where using the raw object library files and not the pre-configured library
* *.lib files that you must generate yourself (manually); I would recommend using Nuget Package Manager with VS2019/2022 if you have it...
* to get the SDL repo from git for you already pre-made unless you are savvy with generating the proper Debug/Release Win32/x64 *.lib files
* necessary to import into your project from SDL's source code... SDL does not have great documentation to properly setup an environment to make
* the *.lib files...
* 
* Regardless, I use the #pragma comment(lib, "<LibraryName>.lib") to import the files directly. AWLAYS DO THIS AFTER YOU INCLUDE YOUR
* HEADERS! I CANNOT STRESS THIS ENOUGH TO DEVELOPERS! The reason is *.lib files use the headers and if the *.lib files are imported
* before the headers you will receive continuous linker errors!
* This section is really overkill but forces the compiler to include the *.lib files even if we declare them... kinda acts as an explicit import...
*/
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2.lib")

int main(int argc, char* argv[]) {
    /*
    * It is recommended to SDL_Init(SDL_INIT_EVERYTHING)
    * rather than initializing every service one by one...
    */
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("SDL_Init(SDL_INIT_EVERYTHING) failed: %s", SDL_GetError());
        return 1;
    }

    /*
    * This block initializes each SDL service one by one, not recommended
    * but it is an option...
    * 
    * Note that we don't use SDL_Init() this is because we want to initialize each service one-by-one...
    * you could also get away with this:
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0) {}
    * but the code above this line is only a really loooonnnnggg alternative to:
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {}
    * The code below this line is how you'd initialize each service individually:
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Video init failed: %s", SDL_GetError());
        return 1;
    }

    if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
        SDL_Log("Audio init failed: %s", SDL_GetError());
        // You can choose to continue or exit depending on your needs
    }

    if (SDL_InitSubSystem(SDL_INIT_EVENTS) != 0) {
        SDL_Log("Events init failed: %s", SDL_GetError());
        // You usually want to poll events from the SDL services so it is a crucial service to have running...
        return 1;
    }
    */

    // Message box is a test...
    // recommended to remove as it does not do anything but test if SDL initialized at minimum video and events services...
	SDL_ShowSimpleMessageBox(
		SDL_MESSAGEBOX_INFORMATION,	// Utilize SDL Info MessageBox format...
		"SDL2-2.32.10",				// Message Box Title
		"Welcome to SDL2!",			// Message Box Message | String
		NULL						// No parent window, NULL as we don't want to attach our MessageBox to an uncreated window...
	);

    // Initialize SDL logic for engine core runtime routines here

	SDL_Quit();
    /*
    * This block would be used if the code above for closing SDL services is not used...
    * It is recommended to close services as they where started in reversed order...
    SDL_QuitSubSystem(SDL_INIT_EVENTS);
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    */
	return 0;
}