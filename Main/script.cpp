#include "script.h"
#include <Mod/App.h>

#include <ModCore/thirdparty/ScriptHook/include/main.h>
#pragma warning(disable : 4244 4305) // double <-> float conversions


void main()
{
    legit::Application::Init();
    while (true) {
        legit::Application::Update();
        WAIT(0);
    }
    legit::Application::Destroy();
}

void ScriptMain()
{
    srand(GetTickCount());
    main();
}
