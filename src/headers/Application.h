#pragma once


#include "raylib.h"


#include "Renderer.h"
#include "UIManager.h"
#include "Graph.h"
#include "utils.h"

class Application
{
private:
    int m_width, m_height;
    std::string m_title;


    struct Renderer renderer;
    UIManager<int> *uimanager;
    Graph<int>* graph;


public:

    Application(int width, int height, std::string title);
    ~Application(); 

    void Init();
    void Run();
    void Close();

};

