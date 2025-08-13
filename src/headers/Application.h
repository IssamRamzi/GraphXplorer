#pragma once


#include "raylib.h"


#include "Renderer.h"
#include "UIManager.h"
#include "Graph.h"

#define         FPS 60
const Color     BgColor = {23,23,23,255};
const Color     TextColor = {220, 220, 220, 255};

class Application
{
private:
    int m_width, m_height;
    char* m_title;


    struct Renderer renderer;
    UIManager<int> *uimanager;
    Graph<int>* graph;


public:

    Application(int width, int height,char* title);
    ~Application(); 

    void Init();
    void Run();
    void Close();

    inline Graph<int>* GetGraph() const { return graph; }
};

