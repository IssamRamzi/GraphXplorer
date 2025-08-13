#pragma once
#include "Graph.h"
#include "raylib.h"
#include "Application.h"

template<class T>
class UIManager
{
private:
    Graph<T>* graph;
    Node<T>* selected_node = nullptr;
    Vector2 mousePosition;
    Camera2D camera;

    
public:


    UIManager(Graph<T>* graph) : graph(graph) {
        camera.target = (Vector2){ 0 };
        camera.offset = (Vector2){ GetRenderWidth() / 2.0f, GetRenderHeight() / 2.0f };
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;
    }
    
    ~UIManager() {}

    Camera GetCamera(){return camera;}
    
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

    void HandleEvent() {


        mousePosition = GetScreenToWorld2D(GetMousePosition(), camera);

        HandleHover();

        HandleCreateNode();
        HandleCreateEdge();
        HandleReset();

        HandleDragNode();
        HandleCamera();
        
    }

    void HandleHover(){
        // Hover node
        bool status = false;
        for(Node<T> *node : graph->GetNodes()){
            if(CheckCollisionPointCircle(mousePosition, node->GetPosition(), NODE_RADIUS)){
                SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
                node->SetColor(HOVER_NODE_COLOR);
                return;
            }
        }
        // TODO : Hover edge


        // Reset everything at the end
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        for(Node<T> *node : graph->GetNodes()){
            node->ResetColor();
        }
    }

    void HandleCreateNode() {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

            for(Node<T> *node : graph->GetNodes()){
                if(node->GetDistance(mousePosition) < MIN_DISTANCE){
                    std::cout << "Impossible to create a node due to the small distance !" << std::endl;
                    return;
                }
            }

            Node<T>* node = new Node<T>(Graph<T>::GetCurrentValue(), mousePosition);
            graph->AddNode(node);    
        }
    }

    void HandleDragNode(){
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            Node<T>* drag;
            for(Node<T> *node : graph->GetNodes()){
                if(CheckCollisionPointCircle(mousePosition, node->GetPosition(), NODE_RADIUS)){
                    drag = node;
                    break;
                }
            }
            try{
                drag->SetColor(SELECTED_NODE_COLOR);
                drag->SetPosition(mousePosition);
            }catch(const std::exception& e){
                std::cerr << e.what();
            }
        }
    }

    void HandleCreateEdge(){
        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
            if(selected_node == nullptr){
                for(Node<T>* node : graph->GetNodes()){
                    if(CheckCollisionPointCircle(mousePosition, node->GetPosition(), NODE_RADIUS)){
                        selected_node = node;
                        std::cout << "Selected node " << node->GetId() << std::endl;
                        return;
                    }
                }
                std::cout << "No node selected" << std::endl;
            } else {
                Node<T>* toLink = nullptr; 
                
                for(Node<T>* node : graph->GetNodes()){
                    if(CheckCollisionPointCircle(mousePosition, node->GetPosition(), NODE_RADIUS)){
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


    void HandleReset(){
        if(IsKeyPressed(KEY_R)){
            delete graph;
            graph = new Graph<T>();
            graph->ResetCurrentValue();
            std::cout << "Reset Done !" << std::endl;
        }
    }



};