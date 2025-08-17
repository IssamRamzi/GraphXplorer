#include <iostream>
#include "GLFW/glfw3.h"

#include "Application.h"
#include "utils.h"

Application::Application(int width, int height,std::string title)
    : m_width(width), m_height(height), m_title(title.c_str())
{
    graph = new Graph<int>();
    uimanager = new UIManager<int>(graph);
}

Application::~Application(){
    delete graph;
    delete uimanager;
}

void Application::Init(){
    logger.Log(INFO, "Initializing GraphXplorer's dependencies");
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(m_width, m_height, m_title.c_str());
    SetTargetFPS(GScreen::FPS);
}

void Application::Close(){
    CloseWindow();
}

void Application::Run(){
    while (!WindowShouldClose()) {
        // Handle input
        uimanager->HandleEvent();
        
        BeginDrawing();
        ClearBackground(GColors::BACKGROUND_COLOR_DARK); 

        BeginMode2D(uimanager->GetCamera());
            
        if (graph && !graph->GetNodes().empty()) {
            renderer.Render(graph);
        }
        
        EndMode2D();
        uimanager->DrawUI();

        
        EndDrawing();
    }
}