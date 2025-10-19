#include "script.h"
#include "keyboard.h"
#include <string>
#include <ctime>
#pragma warning(disable : 4244 4305) // double <-> float conversions
#include "../Project - The End/App.h"
void main()
{
    CModification::Run();
}

void ScriptMain()
{
    srand(GetTickCount());
    main();
}
