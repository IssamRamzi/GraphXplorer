#include <iostream>

#include "Application.h"

int main(int argc, char const *argv[])
{
    int w = 1280, h = 720;
    //std::string title = "GraphXplorer";

    char* title = "Hello World";

    Application program{ w, h, title };
    program.Init();
    program.Run();
    program.Close();
    

    return 0;
}
