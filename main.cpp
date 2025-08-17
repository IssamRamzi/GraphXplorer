#include <iostream>

#include "Application.h"


#define RAYGUI_IMPLEMENTATION
#include "thirdparty/raygui.h"

int main(int argc, char const *argv[])
{
    int w = 1600, h = 900;
    //std::string title = "GraphXplorer";

    std::string title = "Hello World";

    Application program{ w, h, title };
    program.Init();
    program.Run();
    program.Close();


    return 0;
}
