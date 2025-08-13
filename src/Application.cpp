#include <iostream>
#include "GLFW/glfw3.h"

#include "Application.h"

Application::Application(int width, int height,char* title)
    : m_width(width), m_height(height), m_title(title)
{
    graph = new Graph<int>();
    uimanager = new UIManager<int>(graph);
}

Application::~Application(){
    delete graph;
    delete uimanager;
}

void Application::Init(){
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(m_width, m_height, m_title);
    SetTargetFPS(FPS);
}

void Application::Close(){
    CloseWindow();
}

void Application::Run(){
    while (!WindowShouldClose()) {
        // Handle input
        uimanager->HandleEvent();
        
        BeginDrawing();
        BeginMode2D(uimanager->GetCamera());
        ClearBackground(BgColor);
            
        if (graph && !graph->GetNodes().empty()) {
            renderer.Render(graph);
        }
        
        EndMode2D();
        DrawText("GraphXplorer", 30, 45, 32, TextColor);

        
        EndDrawing();
    }
}