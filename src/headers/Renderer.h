#pragma once

#include "Graph.h"
#include "utils.h"

#include "raylib.h"
#include "raygui.h"
#include "UIManager.h"

struct Renderer
{
    template<typename T>
    void DrawNode(Node<T>* node) {
        if(node == nullptr) {
            std::cerr << "Warning: Attempting to draw NULL node!" << std::endl;
            return;
        }
        DrawCircle(node->GetPosition().x, node->GetPosition().y, GSizes::NODE_RADIUS, node->GetColor());


        DrawText(
            TextFormat("%d", node->GetId()), 
            node->GetPosition().x - MeasureText(TextFormat("%d", node->GetId()), GSizes::NODE_TEXT_SIZE) / 2, 
            node->GetPosition().y - GSizes::NODE_TEXT_SIZE / 2, 
            GSizes::NODE_TEXT_SIZE, 
            GColors::NODE_TEXT_COLOR
        );
    }

    template<typename T>
    void DrawEdge(Edge<T> *edge) {
        if(edge == nullptr || edge->GetSource() == nullptr || edge->GetDestination() == nullptr) {
            std::cerr << "Warning: Attempting to draw NULL edge or edge with NULL nodes!" << std::endl;
            return;
        }

        DrawLineEx(
            edge->GetSource()->GetPosition(),
            edge->GetDestination()->GetPosition(),
            5,
            WHITE
        );

        if(Edge<T>::activeWeight){
            // Vector2 mid = utils::CalculateMidPoint(edge->GetSource()->GetPosition(), edge->GetDestination()->GetPosition());
            Vector2 mid = {(edge->GetSource()->GetPosition().x + edge->GetDestination()->GetPosition().x) / 2, 
            (edge->GetSource()->GetPosition().y + edge->GetDestination()->GetPosition().y) / 2};
            DrawText(TextFormat("%.2f", edge->GetWeight()), mid.x - 10, mid.y - 25, 25, BLUE);
        }
        
    }

    template<typename T>
    void Render(Graph<T>* graph){
        if(graph == nullptr) return;
        for(auto e: graph->GetEdges()){
            DrawEdge(e);
        }        

        for(auto n: graph->GetNodes()){
            DrawNode(n);
        }        
    }
};