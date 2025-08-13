#pragma once

#include "Graph.h"
#include "utils.h"

#include "raylib.h"

struct Renderer
{
    template<typename T>
    void DrawNode(Node<T>* node) {
        DrawCircle(node->GetPosition().x, node->GetPosition().y, NODE_RADIUS, node->GetColor());


        DrawText(
            TextFormat("%d", node->GetId()), 
            node->GetPosition().x - MeasureText(TextFormat("%d", node->GetId()), NODE_TEXT_SIZE) / 2, 
            node->GetPosition().y - NODE_TEXT_SIZE / 2, 
            NODE_TEXT_SIZE, 
            NODE_TEXT_COLOR
        );
    }

    template<typename T>
    void DrawEdge(Edge<T> *edge) {
        DrawLineEx(
            edge->GetSource()->GetPosition(),
            edge->GetDestination()->GetPosition(),
            5,
            WHITE
        );

        // Vector2 mid = utils::CalculateMidPoint(edge->GetSource()->GetPosition(), edge->GetDestination()->GetPosition());
        Vector2 mid = {(edge->GetSource()->GetPosition().x + edge->GetDestination()->GetPosition().x) / 2, 
        (edge->GetSource()->GetPosition().y + edge->GetDestination()->GetPosition().y) / 2};

        DrawText(TextFormat("%.2f", edge->GetWeight()), mid.x - 10, mid.y - 25, 25, BLUE);
        
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