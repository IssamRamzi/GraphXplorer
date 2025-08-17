#pragma once
#include "Graph.h"
#include "raylib.h"
#include "Application.h"
#include "utils.h"

#include <deque>

#include "thirdparty/style_dark_raygui.h"
#include "IO.h"

template<class T>
class UIManager
{
private:
    Graph<T>* graph;
    Node<T>* selected_node = nullptr;
    Vector2 mousePosition;
    Camera2D camera;
    Node<T>* dragging_node = nullptr;
    bool dragging = false;
    IO *io;

    std::deque<std::string> logs;

    
public:


    UIManager(Graph<T>* graph) : graph(graph) {
        camera.target = { 0.f, 0.f };
        camera.offset = { GetRenderWidth() / 2.0f, GetRenderHeight() / 2.0f };
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;
        io = new IO();
    }
    
    ~UIManager() {
        delete io;
    }

    const Camera2D GetCamera(){
        return camera;
    }

    void DrawUI(){
        GZones zones;
        // ! Menu
        DrawText("GraphXplorer", 20, 30, GSizes::TITLE_TEXT_SIZE, GColors::NODE_TEXT_COLOR);
        DrawLine(GZones::MenuWidth, 0, GZones::MenuWidth, GetScreenHeight(), WHITE);

        // toggle weight
        // bool toggleState = ;
        ToggleWeight();
        // std::cout << "Active Weight : " << Edge<T>::activeWeight << std::endl;

        //reset btn
        Rectangle resetRec = { 40 , (float)GetScreenHeight() - 80.f, 150, 60};
        if(GuiButton(resetRec, "Reset")){
            Reset();
        }



        // ! Draw
        // TODO : add Slider control
        GuiSlider((Rectangle){ zones.DrawZone.x + zones.DrawZone.width - 200, 50, 175, 16 }, TextFormat("Zoom %0.2f", camera.zoom), NULL, &camera.zoom, 0.0f, 1.0f);


        // ! Terminal 
        DrawLine(GZones::MenuWidth, GetScreenHeight() - zones.TerminalHeight, GetScreenWidth(), GetScreenHeight() - zones.TerminalHeight, WHITE);
        Rectangle panelRec = { zones.MenuWidth,(float)GetScreenHeight() - (float)zones.TerminalHeight, (float)GetScreenWidth() - GZones::MenuWidth, zones.TerminalHeight };
        Rectangle panelContentRec = {0, 0, 340, 340 };
        Rectangle panelView = { 0 };
        Vector2 panelScroll = { 99, -20 };
        GuiScrollPanel(panelRec, NULL, panelContentRec, &panelScroll, &panelView);

    }

    void ToggleWeight() {
        Rectangle toggleRec = { 40 , 80, 150, 60};
        GuiToggle(toggleRec, "Toggle Weight", &Edge<T>::activeWeight); // TODO : Transform this into a GuiToggleSlider

        if (IsKeyPressed(KEY_W)) {
            Edge<T>::activeWeight = !Edge<T>::activeWeight;
        }
    }
    

    void HandleEvent() {
        GZones zones;
        
        mousePosition = GetScreenToWorld2D(GetMousePosition(), camera);
        //initialize
        if(CheckCollisionPointRec(mousePosition, zones.DrawZone)){
            // std::cout << "In Draw Zone" << std::endl;
            HandleHover();
            HandleCreateProcess();
            HandleCreateEdge();
            HandleDragProcess();
        }
        else if(CheckCollisionPointRec(mousePosition, zones.MenuZone)){
            // std::cout << "In Menu Zone" << std::endl;

        }
        else if(CheckCollisionPointRec(mousePosition, zones.TerminalZone)){
            // std::cout << "In Terminal Zone" << std::endl;
            
        }

        //just i think u dont need seperate process
        //HandleCreateNode();
        HandleReset();

        //HandleDragNode();
        HandleCamera();
        HandleFullScreen();
        HandleFileOperations();

    }

    void HandleFileOperations(){
        if(IsKeyPressed(KEY_S) && IsKeyDown(KEY_LEFT_CONTROL)){
            if (graph->GetNodes().size() > 0 && graph->GetEdges().size() > 0 ){
                io->SaveGraph(graph, "file.csv");
                std::cout << "Saving graph" << std::endl;
            }
        }
        if (IsKeyPressed(KEY_L) && IsKeyDown(KEY_LEFT_CONTROL)) {
            Graph<T>* nGraph = new Graph<T>();
            if (io->LoadGraph("file.csv", nGraph)) {
                if(!nGraph->IsValid()) {
                    std::cerr << "Loaded graph is invalid!" << std::endl;
                    delete nGraph;
                    return;
                }
                delete graph;
                graph = nGraph;
                selected_node = nullptr;
                camera.target = Vector2{0.f, 0.f};
                camera.zoom = 1.f;
                std::cout << "Reset Done !" << std::endl;
                std::cout << "Loading graph successful" << std::endl;
                // std::cout << "Nodes size " << nGraph->GetNodes().size() << std::endl;
                std::cout << "Nodes size : " << graph->GetNodes().size() << std::endl;
                for (auto node : graph->GetNodes()) {
                    // std::cout << node->GetId() << std::endl;
                    std::cout << &node << std::endl;
                }
            } else {
                delete nGraph;
                std::cerr << "Failed to load graph" << std::endl;
            }
        }
    }

    
    void HandleCamera() {
        camera.zoom += GetMouseWheelMove() * 0.1f;
        if (camera.zoom < 0.1f) camera.zoom = 0.1f;

        if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
            Vector2 delta = GetMouseDelta();
            delta.x *= -1.0f / camera.zoom;
            delta.y *= -1.0f / camera.zoom;

            camera.target.x += delta.x;
            camera.target.y += delta.y;
        }
    }

    void HandleFullScreen(){
        if(IsKeyPressed(KEY_F11)){
            ToggleFullscreen();
            if(IsWindowFullscreen())
                logs.push_back("Full Screen Mode\n");
            else
                logs.push_back("Windowed Screen Mode\n");
        }
    }

    void HandleHover(){
        bool hovered = false;

        for( Node<T>* node : graph->GetNodes()){
            node->ResetColor();
        }

        for(Node<T> *node : graph->GetNodes()){
            if(CheckCollisionPointCircle(mousePosition, node->GetPosition(), GSizes::NODE_RADIUS)){
                SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
                node->SetColor(GColors::HOVER_NODE_COLOR);
                hovered = true;
                return;
            }
        }
        if(!hovered){
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }

    void HandleCreateProcess() {
        // checking 
        Node<T>* hit_node = nullptr;
        for(Node<T> *node : graph->GetNodes()){
            if(CheckCollisionPointCircle(mousePosition, node->GetPosition(), GSizes::NODE_RADIUS)){
                hit_node = node;
                break;
            }
        }
        if(hit_node){
            // process of hit
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                hit_node->SetColor(GColors::SELECTED_NODE_COLOR);
                hit_node->SetPosition(mousePosition);
            }
        }
        else{
            // when click the empty space
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

            for(Node<T> *node : graph->GetNodes()){
                if(node->GetDistance(mousePosition) < GSizes::MINIMUM_NODE_DISTANCE){
                    std::cout << "too close to make another node!" << std::endl;
                    return;
                }
            }
            logs.push_back(std::format("Created a new node with a value of {}\n", Graph<T>::GetCurrentValue()));
            Node<T>* node = new Node<T>(Graph<T>::GetCurrentValue(), mousePosition);
            std::cout << node << std::endl;
            graph->AddNode(node);

        }
        }
    }

    void HandleDragProcess()
    {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            dragging_node = nullptr;
            for (Node<T>* node : graph->GetNodes()) {
                if (CheckCollisionPointCircle(mousePosition, node->GetPosition(), GSizes::NODE_RADIUS)) {
                    dragging_node = node;
                    dragging = true;
                    break;
                }
            }
            if(!dragging_node){
                for (Node<T>* node : graph->GetNodes()){
                    if(node->GetDistance(mousePosition) < GSizes::MINIMUM_NODE_DISTANCE){
                        std::cout << "too close" << std::endl;
                        return;
                    }
                }
            }
        }
        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            dragging = false;
            dragging_node = nullptr;
        }

        //check all of them
        if(dragging && dragging_node){
            dragging_node->SetColor(GColors::SELECTED_NODE_COLOR);
            dragging_node->SetPosition(mousePosition);
        }
    }

    void HandleDragNode(){

        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Node<T>* drag;
            for(Node<T> *node : graph->GetNodes()){
                if(CheckCollisionPointCircle(mousePosition, node->GetPosition(), GSizes::NODE_RADIUS)){
                    drag = node;
                    break;
                }
            }
            try{

                drag->SetColor(GColors::SELECTED_NODE_COLOR);
                drag->SetPosition(mousePosition);
            }catch(const std::exception& e){
                std::cerr << e.what();
            }
        }
    }

    void HandleCreateEdge(){
        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
            if(!selected_node){
                for(Node<T>* node : graph->GetNodes()){
                    if(CheckCollisionPointCircle(mousePosition, node->GetPosition(), GSizes::NODE_RADIUS)){
                        selected_node = node;
                        std::cout << "Selected node " << node->GetId() << std::endl;
                        return;
                    }
                }
                std::cout << "No node selected" << std::endl;
            } else {
                Node<T>* toLink = nullptr; 
                
                for(Node<T>* node : graph->GetNodes()){
                    if(CheckCollisionPointCircle(mousePosition, node->GetPosition(), GSizes::NODE_RADIUS)){
                        toLink = node;
                        break; 
                    }
                }
                
                if(toLink != nullptr && toLink != selected_node){
                    bool edgeExists = false;
                    for(Edge<T>* existingEdge : graph->GetEdges()){
                        if((existingEdge->GetSource() == selected_node && existingEdge->GetDestination() == toLink) ||
                        (existingEdge->GetSource() == toLink && existingEdge->GetDestination() == selected_node)){
                            edgeExists = true;
                            break;
                        }
                    }
                    
                    if(!edgeExists){
                        Edge<T>* edge = new Edge<T>(selected_node, toLink);
                        graph->AddEdge(edge);
                        std::cout << "Created edge from node " << selected_node->GetId() 
                                << " to node " << toLink->GetId() << std::endl;
                    } else {
                        std::cout << "Edge already exists between these nodes" << std::endl;
                    }
                } else if(toLink == selected_node) {
                    std::cout << "Cannot create edge to the same node" << std::endl;
                } else {
                    std::cout << "No target node found" << std::endl;
                }
                
                selected_node = nullptr;
            }
        }
    }

    void Reset(){
        graph->Reset();
        selected_node = nullptr;
        camera.target = Vector2(0.f,0.f);
        camera.zoom = 1.f;
        std::cout << "Reset Done !" << std::endl;
    }

    void HandleReset(){
        if(IsKeyPressed(KEY_R)){
            Reset();
        }
    }



};